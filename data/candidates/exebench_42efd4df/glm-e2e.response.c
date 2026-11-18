int getMax(int a, int b, int c, int *max_val) {
    int index = 1;
    int max = a;
    
    if (max < b) {
        max = b;
        index = 2;
    }
    
    if (max < c) {
        max = c;
        index = 3;
    }
    
    *max_val = max;
    return index;
}