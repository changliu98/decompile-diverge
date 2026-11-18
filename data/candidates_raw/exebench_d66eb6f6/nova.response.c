int func0(char *str, int size) {
    int i, j, k, l;
    if (size > 5) {
        k = 0;
    } else {
        for (i = 0, j = 0; j < size; j++) {
            l = i * 100 + (str[j] / 16) * 10 + (str[j] % 16);
            i = l;
        }
        k = i;
    }
    return k;
}