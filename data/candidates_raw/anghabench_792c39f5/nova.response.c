int func0(int player) {
    int i;
    int flag = 1;
    int *p = &flag;
    int color;
    if (*p == 1) {
        color = WHITE;
    } else {
        color = BLACK;
    }
    if (color!= player) {
        return 1;
    } else {
        return 0;
    }
}