static void od_filter_dering_direction_offsets(int *order, int n, int stride)
{
    int i, j;

    if (n <= 4) {
        i = n - 2;
        for (j = 1; ; j++) {
            if (j >= 4)
                return;
            order[j - 1] = (i * j / 2) * stride + j;
        }
    } else {
        i = 6 - n;
        for (j = 1; ; j++) {
            if (j >= 4)
                return;
            order[j - 1] = j * stride + (i * j / 2);
        }
    }
}