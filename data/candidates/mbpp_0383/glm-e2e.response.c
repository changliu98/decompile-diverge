int func0(int n) {
    int bits = 0;
    int i = 0;
    int temp = n;
    
    while (temp > 0) {
        if (i % 2 == 0) {
            bits |= (1 << i);
        }
        i++;
        temp >>= 1;
    }
    
    return n ^ bits;
}