void func0(char *line, float *x, float *y, int *num) {
    num[0] = line[0] - '0';
    if (num[0] >= 0 && num[0] <= 9) {
        if (num[0] == 1) {
            *x = *x / 2;
        }
        *y = *y + (float)num[0] * 3;
    }
}