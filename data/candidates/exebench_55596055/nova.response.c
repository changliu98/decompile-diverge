int clean_fd(int x, int *a, int *len) {
    int i = 0;
    while (i < 3) {
        if (a[i] == x) {
            a[i] = 0;
            break;
        }
        i++;
    }
    free(a);
    *len = *len - 1;
    return *len;
}