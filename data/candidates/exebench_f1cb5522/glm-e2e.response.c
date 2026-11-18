void argorder(int a, int b, int *c, int *d) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    *c = a;
    *d = b;
}