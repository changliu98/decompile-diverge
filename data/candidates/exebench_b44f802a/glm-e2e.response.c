void YvVfilterCoef(double *out, double x) {
    // Constants loaded from memory
    const double c1 = 0.5;       // 0x3fe0000000000000
    const double c2 = 0.25;      // 0x3fd0000000000000
    const double c3 = 0.125;     // 0x3fc0000000000000
    const double threshold = 1.0;// 0x3ff0000000000000
    
    // Polynomial coefficients
    const double p1 = 0.5;       // 0x3fe0000000000000
    const double p2 = 0.25;      // 0x3fd0000000000000
    const double p3 = 0.125;     // 0x3fc0000000000000
    const double p4 = 0.0625;    // 0x3fb0000000000000
    const double p5 = 0.03125;   // 0x3fa0000000000000
    const double p6 = 0.015625;  // 0x3f90000000000000
    const double p7 = 0.0078125; // 0x3f80000000000000

    double c1_sq = c1 * c1;
    double c2_sq = c2 * c2;
    
    double t;
    if (threshold < x) {
        t = x * p1 + p2 + x * x * p3;
    } else {
        t = (x - threshold) * p4 + p5;
    }
    
    double t_sq = t * t;
    
    double denom = (c1 + t) * (c1_sq + c2_sq + p6 * c1 * t + t_sq);
    
    double a1 = -t * (p6 * c1 + c1_sq + c2_sq + (2 * c1 + p7 * c2) * t + p5 * t_sq) / denom;
    double a2 = t_sq * (2 * c1 + c2 + p5 * t) / denom;
    double a3 = -t_sq * t / denom;
    double a0 = c1 * (c1_sq + c2_sq) / denom;
    
    // The output array is a 7-tap symmetric filter
    out[0] = -a3;
    out[1] = -a2;
    out[2] = -a1;
    out[3] = a0;
    out[4] = a1;
    out[5] = a2;
    out[6] = a3;
}