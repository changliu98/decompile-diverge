float spline_cubic_val(int n, const float *t, float tval, const float *y, const float *ypp) {
    int left = n - 2;
    int i = 0;
    
    while (i < n - 1) {
        if (tval < t[i + 1]) {
            left = i;
            break;
        }
        i++;
    }
    
    float dt = tval - t[left];
    float h = t[left + 1] - t[left];
    
    double yval = y[left];
    double ypp_left = ypp[left];
    double ypp_left_1 = ypp[left + 1];
    double y_left = y[left];
    double y_left_1 = y[left + 1];
    
    double term1 = (ypp_left_1 / 6.0) + (ypp_left / 2.0);
    term1 = -term1 * h + (y_left_1 - y_left) / h;
    
    double term2 = (ypp_left / 2.0) * dt;
    double term3 = ((ypp_left_1 - ypp_left) * dt) / (6.0 * h);
    double term4 = (3.0 * ypp_left) * dt;
    
    double temp = term2 + term3 + term4;
    temp = temp * dt;
    temp = temp + term1;
    temp = temp * dt;
    temp = temp + yval;
    
    return (float)temp;
}