int func0(int x) {
    int i, j, k;
    if ((x & (x + 1)) == 0)
        return x;
    else {
        i = 0;
        j = x;
        k = 0;
        while (j!= 0) {
            if (j % 2 == 0) {
                i = k;
            }
            k++;
            j = j >> 1;
        }
        x = x | (1 << i);
    }
    return x;
}