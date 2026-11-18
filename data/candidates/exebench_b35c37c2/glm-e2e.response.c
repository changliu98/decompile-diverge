void itox(short int n, char *s) {
    char temp[2];
    short int i = 0;
    short int len;

    if (n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    while (n != 0) {
        short int rem = n % 16;
        if (rem < 10) {
            temp[i++] = rem + '0';
        } else {
            temp[i++] = (rem - 10) + 'a';
        }
        n /= 16;
    }

    len = i;
    while (i > 0) {
        s[len - i] = temp[i - 1];
        i--;
    }
    s[len] = '\0';
}