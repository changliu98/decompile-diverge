int mean3(int a, int b, int c, int d, int *e) {
    int mean = (a + b + c) / 3;
    
    if (e != NULL) {
        int abs_a = abs(a - mean);
        int abs_b = abs(b - mean);
        int abs_c = abs(c - mean);
        
        int max_abs = (abs_a > abs_b) ? abs_a : abs_b;
        max_abs = (max_abs > abs_c) ? max_abs : abs_c;
        
        *e = max_abs;
    }
    
    if (a < d && b < d && c < d) {
        return mean;
    } else {
        return (mean > d) ? d : mean;
    }
}