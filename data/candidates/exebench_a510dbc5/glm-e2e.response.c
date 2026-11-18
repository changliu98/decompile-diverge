void chartobit(int c, char *str) {
    int i = 7;
    while (i > 0) {
        str[i] = (c % 2 == 1) ? '1' : '0';
        c /= 2;
        i--;
    }
    str[0] = (c % 2 == 1) ? '1' : '0';
}