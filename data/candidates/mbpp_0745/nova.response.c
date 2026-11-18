void func0(int a, int b, int c[], int *n) {
    int i, j, k;
    bool flag;
    *n = 0;
    for (i = a; i <= b; i++) {
        flag = true;
        j = i;
        while (j > 0) {
            k = j % 10;
            if (k == 0 || i % k!= 0) {
                flag = false;
                break;
            }
            j /= 10;
        }
        if (flag) {
            c[*n] = i;
            (*n)++;
        }
    }
}