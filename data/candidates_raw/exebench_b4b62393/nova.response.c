void func0(int *a, int *b) {
    if (a!= b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}