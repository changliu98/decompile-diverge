void mult(double *a, double *b, double *c) {
    int i = 0;
    int k = 0;
    
    while (i < 4) {
        c[i] = a[k] * b[0];
        k++;
        
        c[i] = c[i] + a[k] * b[1];
        k++;
        
        c[i] = c[i] + a[k] * b[2];
        k++;
        
        c[i] = c[i] + a[k] * b[3];
        k++;
        
        i++;
    }
}