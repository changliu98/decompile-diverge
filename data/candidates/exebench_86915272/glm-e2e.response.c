void rahms(double value, int *out1, int *out2, float *out3) {
    double temp = value;
    
    // If value is negative, add 360.0
    if (0.0 > temp) {
        temp += 360.0;
    }
    
    // If value is greater than 360.0, subtract 360.0
    if (temp > 360.0) {
        temp -= 360.0;
    }
    
    // Divide by 30.0
    temp /= 30.0;
    
    // Extract integer part and store in out1
    int i1 = (int)temp;
    *out1 = i1;
    
    // Extract fractional part, multiply by 60.0
    temp = (temp - (double)i1) * 60.0;
    
    // Extract integer part and store in out2
    int i2 = (int)temp;
    *out2 = i2;
    
    // Extract fractional part, multiply by 60.0, and store in out3
    temp = (temp - (double)i2) * 60.0;
    *out3 = (float)temp;
}