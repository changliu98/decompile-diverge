void intToString(int n, char *str)
{
    int i, len;
    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    for (len = 0; n != 0; n /= 10, ++len)
        ;
    str[len] = '\0';
    for (i = len - 1; i >= 0; i--) {
        str[i] = (n % 10) + '0';
        n /= 10;
    }
}