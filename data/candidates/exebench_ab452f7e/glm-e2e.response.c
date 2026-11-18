int maxdig(int *n, int *m) {
    int res;
    
    if (*n == 0) {
        res = *m;
    } else {
        dig = *n % 10;
        if (dig > *m) {
            *m = dig;
        }
        *n = *n / 10;
        maxdig(n, m);
        res = *m; 
    }
    
    return res;
}