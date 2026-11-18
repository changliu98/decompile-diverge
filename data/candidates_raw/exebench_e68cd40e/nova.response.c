void func0(int *p) {
    int i;
    for (i = 0; i < 21; i++) {
        *(p + i) = 0;
    }
}