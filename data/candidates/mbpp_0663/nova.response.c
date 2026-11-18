int func0(int n, int x, int y) {
    int i, j, k, l;
    i = INT_MIN;
    j = 0;
    while (1) {
        if (j > n)
            break;
        if (j % x == y) {
            if (i < j)
                i = j;
        }
        j++;
    }
    if (i < 0 && i > n)
        l = -1;
    else
        l = i;
    return l;
}