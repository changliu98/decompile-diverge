void logFibonacci(int n, long *f1, long *f2) {
    if (n == 2) {
        *f2 = 1;
        *f1 = 1;
        return;
    }
    if (n == 0) {
        *f2 = 0;
        *f1 = 0;
        return;
    }
    
    int k = n / 2;
    
    if (k % 2 == 0) {
        logFibonacci(k, f1, f2);
        
        long a = (2 * (*f2) + (*f1)) * (*f1);
        long b = (*f2) * (*f2) + (*f1) * (*f1);
        
        *f1 = a;
        *f2 = b;
    } else {
        logFibonacci(k - 1, f1, f2);
        
        long a = (2 * (*f2) + (*f1)) * (*f1);
        long b = (*f2) * (*f2) + (*f1) * (*f1);
        
        *f2 = a + b;
        *f1 = *f2 + a;
    }
}