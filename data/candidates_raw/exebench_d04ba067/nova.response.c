static int func0(int value, char *ptr) {
    char temp[10] = {0};
    int i = 0, j = 0;

    do {
        temp[i++] = (char)((value % 10) + '0');
        value /= 10;
    } while (value);

    do {
        ptr[j++] = temp[i - j - 1];
    } while (j < i);

    return j;
}