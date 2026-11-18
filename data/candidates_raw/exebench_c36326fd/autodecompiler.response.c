void copy(int from[], int to[])
{
    int i, j;
    i = 10 - 1;
    j = 15 - 1;
    while (i >= 0) {
        to[j] = from[i];
        --i;
        --j;
    }
    while (j + 1)
        to[j--] = 0;
}