int func0(int n) {
    int i = 1, j = 2;
    while (1) {
        if (j <= n) {
            i *= j;
            while (i % 10 == 0)
                i /= 10;
        } else
            break;
        j++;
    }
    if (i >= 10)
        i /= 10;
    return (int)floor(i);
}