int func0(int n) {
    int result = 0;
    int i = n;
    while (i > 0) {
        if ((i & (i - 1)) == 0) {
            result = i;
            break;
        }
        i--;
    }
    return result;
}