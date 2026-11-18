int zuchk_(double *a, double *b, int *c, double *d, double *e) {
    double abs_a = (*a >= 0.0) ? *a : -*a;
    double abs_b = (*b >= 0.0) ? *b : -*b;
    double max_val = (abs_a > abs_b) ? abs_a : abs_b;
    
    *c = 0;
    
    if (max_val > *d) {
        return 0;
    }
    
    double min_val = (abs_a > abs_b) ? abs_b : abs_a;
    double ratio = max_val / *e;
    
    if (ratio > min_val) {
        *c = 1;
    }
    
    return 0;
}