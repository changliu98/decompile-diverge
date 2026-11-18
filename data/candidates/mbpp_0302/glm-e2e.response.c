int func0(int n) {
    int res;
    int count;
    
    if (n == 0) {
        res = 0;
    } else {
        count = 0;
        n = n / 2;
        while (n > 0) {
            n = n / 2;
            count++;
        }
        res = 1 << count;
    }
    
    return res;
}