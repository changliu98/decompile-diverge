void func0(int min, int max, int *val) {
    if (*val < min)
        *val = min;
    else if (*val > max)
        *val = max;
}