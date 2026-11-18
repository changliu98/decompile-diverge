int func0(int *list, int len) {
    int i;
    for (i = 1; ; i++) {
        if (i >= len) {
            break;
        }
        if (list[i] < list[i-1]) {
            return i;
        }
    }
    return 0;
}