static int get_name_len(int n, const unsigned char *x, size_t len,
                         size_t max, int *cnt, int *sum)
{
    int ret;
    unsigned short ch;
    const unsigned char *p;

    if (n > 10) {
        ret = 320043;
        goto err;
    }
    if (len < max) {
        ret = 320043;
        goto err;
    }
    *cnt = 0;
    *sum = 0;
    p = x;
    for (;;) {
        if (*p == 0) {
            ret = 320043;
            goto err;
        }
        if ((*p & 0xc0)!= 0xc0) {
            ret = 320043;
            goto err;
        }
        ch = ntohs(*((unsigned short *)p));
        ch ^= (unsigned short)(0xff00);
        ch = bswap16(ch);
        if (ch > (unsigned short)(len - max)) {
            ret = 320043;
            goto err;
        }
        ret = get_name_len(n + 1, x + ch, len, max, cnt, sum);
        if (ret!= 0)
            goto err;
        *cnt += 2;
        *sum += ch;
        ret = 0;
        goto err;
    err:
        if (*p == 0)
            break;
        p++;
        *cnt += 1;
        *sum += *p;
    }
    return ret;
}