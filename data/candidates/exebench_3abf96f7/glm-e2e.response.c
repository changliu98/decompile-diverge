void MassRelease(double *a, double *b, double *c, double *d) {
    if (*a > 0.0) {
        double v1 = *a * 0.5;
        double v2 = *a * 1.0; // Likely just *a, but kept as multiplication to match assembly
        if (*b >= v1) {
            *d += v1;
            *a -= v1;
            *b -= v1;
            
            double v3;
            if (0.0 > *a) {
                v3 = 0.0;
            } else {
                double v4 = *a - 0.0;
                if (v2 > v4) {
                    v3 = *a - 0.0;
                } else {
                    v3 = v2;
                }
            }
            
            *c += v3;
            *a -= v3;
            
            MassRelease(a, b, c, d);
        } else {
            double v5;
            if (*a > *b) {
                v5 = *b;
            } else {
                v5 = *a;
            }
            
            *d += v5;
            *a -= v5;
        }
    } else {
        double v6;
        if (*a > *b) {
            v6 = *b;
        } else {
            v6 = *a;
        }
        
        *d += v6;
        *a -= v6;
        *b = 0.0;
    }
}