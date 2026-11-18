void func0(int a, int b, int *min, int *max) {
    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    *min = a;
    *max = b;
}