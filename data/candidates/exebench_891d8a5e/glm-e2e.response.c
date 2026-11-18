void decdms(double coord, int *deg, int *min, float *sec) {
    double temp = coord;
    
    // Extract degrees
    int d = (int)temp;
    *deg = d;
    
    // Get fractional part
    temp = temp - (double)d;
    
    // Take absolute value of the fractional part
    if (temp < 0.0) {
        temp = -temp;
    }
    
    // Extract minutes
    temp = temp * 60.0;
    int m = (int)temp;
    *min = m;
    
    // Extract seconds
    temp = (temp - (double)m) * 60.0;
    *sec = (float)temp;
}