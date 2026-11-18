void parabolic_interpolation(float y1, float y2, float y3, int x2, float *y_out, int *x_out) {
    // Calculate the fractional offset 'p'
    float p = (y1 - y3) / (y1 - 2.0f * y2 + y3) * 0.5;
    
    // Update the x-coordinate
    *x_out = x2 + (int)p;
    
    // Update the y-coordinate
    *y_out = y2 + 0.5 * (y1 - y3) * p;
}