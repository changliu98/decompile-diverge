void test1(short n, int *a) {
    short i = 0;
    while (i < n) {
        i++;
        *(a + i) = 0;
    }
}