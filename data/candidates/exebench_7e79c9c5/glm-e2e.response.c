float spline_cubic_val(int n, float t[], float tval, float y[], float ypp[]) {
    int i;
    int left = n - 2;
    
    for (i = 0; i < n - 1; i++) {
        if (tval < t[i + 1]) {
            left = i;
            break;
        }
    }
    
    float dt = tval - t[left];
    float h = t[left + 1] - t[left];
    
    double yval = y[left] 
                + dt * ( (y[left + 1] - y[left]) / h
                       - (ypp[left + 1] / 6.0 + ypp[left] / 2.0) * h
                       + dt * ( (ypp[left + 1] - ypp[left]) / (2.0 * h)
                              + dt * ( (ypp[left] * 2.0 + (ypp[left + 1] - ypp[left]) * dt / h) / 6.0 ) ) );
                
    return (float)yval;
}