void af_filter_bilinear(const float *a, const float *b, float *scale, float fs, float *coef) {
    // The constants loaded from memory correspond to 2.0, 4.0, and 8.0
    // The compiler promotes the float arithmetic to double precision for intermediate calculations
    
    // Calculate denominator: a0 + a1*(2*fs) + a2*(2*fs)^2
    double den = (double)a[0] + (double)a[1] * (2.0 * fs) + (double)a[2] * (4.0 * fs * fs);
    
    // Calculate numerator: b0 + b1*(2*fs) + b2*(2*fs)^2
    double num = (double)b[0] + (double)b[1] * (2.0 * fs) + (double)b[2] * (4.0 * fs * fs);
    
    // Update the scale factor
    *scale *= (float)(num / den);
    
    // Calculate and store digital filter coefficients
    // coef[0] = (b0 + b1*(-2*fs) + b2*(4*fs^2)) / den
    *coef++ = (float)(((double)b[0] + (double)b[1] * (-2.0 * fs) + (double)b[2] * (4.0 * fs * fs)) / den);
    
    // coef[1] = (2*b0 - 2*b2*(4*fs^2)) / den
    *coef++ = (float)((2.0 * (double)b[0] - 2.0 * (double)b[2] * (4.0 * fs * fs)) / den);
    
    // coef[2] = (b0 - b1*(2*fs) + b2*(4*fs^2)) / den
    *coef++ = (float)(((double)b[0] - (double)b[1] * (2.0 * fs) + (double)b[2] * (4.0 * fs * fs)) / den);
    
    // coef[3] = (a0 + a1*(-2*fs) + a2*(4*fs^2)) / den
    *coef++ = (float)(((double)a[0] + (double)a[1] * (-2.0 * fs) + (double)a[2] * (4.0 * fs * fs)) / den);
    
    // coef[4] = (2*a0 - 2*a2*(4*fs^2)) / den
    *coef++ = (float)((2.0 * (double)a[0] - 2.0 * (double)a[2] * (4.0 * fs * fs)) / den);
    
    // coef[5] = (a0 - a1*(2*fs) + a2*(4*fs^2)) / den
    *coef = (float)(((double)a[0] - (double)a[1] * (2.0 * fs) + (double)a[2] * (4.0 * fs * fs)) / den);
}