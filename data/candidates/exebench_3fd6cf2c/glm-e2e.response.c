void od_filter_dering_direction_offsets(int *offsets, int dir, int stride) {
    int base;
    int i;
    int temp;

    if (dir <= 4) {
        base = dir - 2;
        for (i = 1; i <= 3; i++) {
            offsets[i - 1] = ((base * i) / 2) * stride + i;
        }
    } else {
        base = 6 - dir;
        for (i = 1; i <= 3; i++) {
            temp = i * stride;
            offsets[i - 1] = temp + ((base * i) / 2);
        }
    }
}