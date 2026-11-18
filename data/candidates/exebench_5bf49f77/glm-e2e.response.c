float catmull_rom_val(int n, const float *ts, float t, const float *pts, const float *unused) {
    int i;
    int idx = n - 2;
    
    // Find the segment index `idx` such that ts[idx+1] > t
    for (i = 0; i < n - 2; i++) {
        if (ts[i + 1] > t) {
            idx = i;
            break;
        }
    }
    
    // Local parameters for the current segment
    float p0 = pts[idx];
    float p1 = pts[idx + 1];
    float dt = ts[idx + 1] - ts[idx];
    float x = (t - ts[idx]) / dt;
    
    // Powers of x
    float x2 = x * x;
    float x3 = x2 * x;
    
    // Calculate the 4 cubic basis functions (h00, h10, h01, h11)
    // The compiler optimized these using double-precision arithmetic.
    float h00 = (float)((double)x3 + (-1.5 * (double)x2) + (2.0 * (double)x) + 0.0);
    float h10 = (float)((double)x3 + (-1.5 * (double)x2) + (double)x + 0.0);
    float h01 = (float)((-0.5 * (double)x2) + (2.0 * (double)x3));
    float h11 = (float)((double)x3 + (-0.5 * (double)x2));
    
    // Compute and return the interpolated value
    return h00 * p0 + h10 * dt * p0 + h01 * p1 + h11 * dt * p1;
}