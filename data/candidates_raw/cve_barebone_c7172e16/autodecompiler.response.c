static int get_name_len(int depth, char *buf, char *p, char *end, int *len,
                        int *namelen)
{
    unsigned short addr;
    int status, l, n, plen, nlen;

    if (depth > 10) {
        return ((32 + 100000) + 1);
    }
    if (p >= end) {
        return ((32 + 100000) + 1);
    }

    *len = 0;
    *namelen = 0;
    p = p;
    while (1) {
        if (*p == '\0') {
            break;
        }
        if ((*p & 0xc0) == 0xc0) {
            nlen = 0;
            pj_memcpy(&addr, p, 2);
            addr ^= __ZL8foldCaset((unsigned short)(0xc000));
            addr = __ZL8foldCaset_0(addr);
            if (addr >= (end - buf)) {
                return ((32 + 100000) + 1);
            }
            status = get_name_len(depth + 1, buf, buf + addr, end, &plen,
                                  &nlen);
            if (status != 0) {
                return status;
            }
            *len += 2;
            *namelen += nlen;
            return 0;
        }
        l = (unsigned char)*p;
        if (p + 1 + l + 1 > end) {
            return ((32 + 100000) + 1);
        }
        p += 1 + l + 1;
        *len += 1 + l + 1;
        if (*(p) != '\0') {
            l++;
        }
        *namelen += l;
    }
    ++p;
    ++*len;
    return 0;
}