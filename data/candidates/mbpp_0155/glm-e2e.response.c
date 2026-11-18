int func0(int n) {
    int result = 0;
    int i = 0;
    int temp = n;
    
    while (temp > 0) {
        if (i % 2 == 1) {
            result = result | (1 << i);
        }
        i++;
        temp = temp >> 1;
    }
    
    return n ^ result;
}