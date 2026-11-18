double frexp(double x, int *exp) {
    int e = 0;
    double scale = 0.5;
    
    // If x is negative, make it positive and adjust the scale to 1.0
    if (x < 0.0) {
        x = -x;
        scale = 1.0;
    }
    
    // If x is 0.0 or NaN, skip the normalization loops
    if (x != 0.0) {
        // Scale down large numbers
        while (x >= 0.5) {
            e += 1;
            x *= 0.5;
        }
        
        // Scale up small numbers
        while (x < 0.5) {
            e -= 1;
            x *= 2.0;
        }
    }
    
    *exp = e;
    return x * scale;
}