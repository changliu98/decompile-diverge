void setLoopIters(int *out, double a, double b, double c) {
    double total = a * b * (double)*out;
    
    if (total > c) {
        *out = (int)(((double)*out * c) / total);
        if (*out < 2) {
            *out = 2;
        }
    }
}