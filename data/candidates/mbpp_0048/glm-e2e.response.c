int func0(int n) {
    int i = 0;
    int result = 0;
    int temp = n;
    while (temp > 0) {
        if (i % 2 == 0) {
            result = result | (1 << i);
        }
        i = i + 1;
        temp = temp >> 1;
    }
    return n | result;
}