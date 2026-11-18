int itostr(char *buf, int buflen, int x)
{
    char *beg = buf;
    int cnt = 0;

    if (buflen <= 0)
        return 0;

    if (x < 0) {
        *buf = '-';
        buf++;
        buflen--;
        x = -x;
        cnt++;
    }

    while (buflen > 0) {
        *buf = '0' + (x % 10);
        cnt++;
        buflen--;
        if (buflen > 0) {
            x /= 10;
            if (x == 0)
                break;
            buf++;
        }
    }

    if (buflen > 0) {
        *++buf = '\0';
    }

    while (beg < buf) {
        char ch = *beg;
        *beg = *buf;
        *buf = ch;
        beg++;
        buf--;
    }

    return cnt;
}