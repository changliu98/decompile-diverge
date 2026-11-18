double func0(double *arr, int n) {
    double x = 0.0;
    double p = arr[0];
    
    for (int i = 1; i < n; i++) {
        double term = 1.0;
        for (int j = 0; j < i; j++) {
            term *= x;
        }
        p += arr[i] * term;
    }
    
    while (fabs(p) > 1e-10) {
        double dp = 0.0;
        for (int i = 1; i < n; i++) {
            double term = 1.0;
            for (int j = 1; j < i; j++) {
                term *= x;
            }
            dp += (double)i * arr[i] * term;
        }
        
        x -= p / dp;
        
        p = arr[0];
        for (int i = 1; i < n; i++) {
            double term = 1.0;
            for (int j = 0; j < i; j++) {
                term *= x;
            }
            p += arr[i] * term;
        }
    }
    
    return x;
}