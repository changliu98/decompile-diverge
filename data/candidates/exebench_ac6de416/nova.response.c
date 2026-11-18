void adjust_mode_num(int *x) {
    if (*x > 9)
        *x = 9;
    else if (*x < 0)
        *x = 0;
}