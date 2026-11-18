void getNums(int *p) {
    int i = 0;
    while (i < 5) {
        *p = i * 2;
        p++;
        i++;
    }
}