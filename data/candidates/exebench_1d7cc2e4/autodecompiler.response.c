void logFibonacci(int n, long long int *f1, long long int *f2) {
    if(n == 2) {
        *f2 = 1;
        *f1 = 1;
        return;
    } else if(n == 0) {
        *f2 = 0;
        *f1 = 0;
        return;
    }

    long long int x = n/2;

    if(x%2 == 0) {
        long long int t1, t2;
        logFibonacci(x, f1, f2);
        t1 = (*f2)*2*(*f1) + (*f1)*(*f1);
        t2 = (*f2)*(*f2) + (*f1)*(*f1);
        *f1 = t1;
        *f2 = t2;
    } else {
        long long int t1, t2;
        logFibonacci(x-1, f1, f2);
        t1 = (*f2)*2*(*f1) + (*f1)*(*f1);
        t2 = (*f2)*(*f2) + (*f1)*(*f1);
        *f2 = t1+t2;
        *f1 = t1+t2+t1;
    }
}