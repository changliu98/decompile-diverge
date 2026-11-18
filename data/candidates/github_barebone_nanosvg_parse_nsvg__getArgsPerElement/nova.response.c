int nsvg__getArgsPerElement(char c) {
    int i, j;
    long long int x;
    x = c;
    x = x - 48;
    if (x >= 0 && x <= 9) {
        i = x;
    } else if (x == 10) {
        i = 1;
    } else if (x == 11) {
        i = 2;
    } else if (x == 12) {
        i = 4;
    } else if (x == 14) {
        i = 6;
    } else if (x == 16) {
        i = 7;
    } else if (x == 17) {
        i = 0;
    } else {
        i = -1;
    }
    return i;
}