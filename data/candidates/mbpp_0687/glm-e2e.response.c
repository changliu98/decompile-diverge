int func0(int a, int b) {
    int min_val = (a < b) ? a : b;
    int max_val = (a > b) ? a : b;
    
    if (min_val == 0) {
        return max_val;
    } else if (min_val == 1) {
        return 1;
    } else {
        return func0(min_val, max_val % min_val);
    }
}