int func0(int n) {
    int i, j, k;
    char flag;
    for (i = 0; i < 10; i++) {
        k = n;
        j = 0;
        while (k > 0) {
            if (k % 10 == i)
                j++;
            if (j > i) {
                flag = 0;
                break;
            }
            k /= 10;
        }
        if (flag == 0)
            break;
    }
    if (i % 2 == 0)
        return 0;
    else
        return 1;
}