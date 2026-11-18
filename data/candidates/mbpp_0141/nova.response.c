void func0(int *a, int n) {
    int i = n;
    while (1) {
        if (i > 1) {
            int p = partition(a, n);
            if (p == i - 1)
                break;
            swap(a, 0, p);
            swap(a, 0, i - 1);
        }
        i--;
    }
}