int func0(int n) {
    int result;
    int pos;
    int temp;
    int i;

    if ((n & (n + 1)) == 0) {
        result = n;
    } else {
        pos = 0;
        temp = n;
        i = 0;
        while (temp != 0) {
            if ((temp & 1) == 0) {
                pos = i;
            }
            i++;
            temp >>= 1;
        }
        result = n | (1 << pos);
    }
    return result;
}