int doit(int *ptr, int val) {
    int result;
    
    if (*ptr > val) {
        *ptr = val;
        result = 1;
    } else {
        result = 0;
    }
    
    return result;
}