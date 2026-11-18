static int get_name_len(int depth, char *buf, char *p, char *eom,
                        unsigned int *len, unsigned int *namelen)
{
    int status;
    unsigned short addr;
    unsigned int label_len, dummy;
    unsigned int nlen;
    char *p1;

    if (depth > 10) {
        return ((32 + 100000) + 1);
    }

    *len = 0;
    *namelen = 0;
    p1 = p;

    while (1) {

        if (*p1 == '\0') {
            ++p1;
            ++(*len);
            return 0;
        }


        if ((*p1 & 0xc0) == 0xc0) {
            nlen = 0;
            pj_memcpy(&addr, p1, 2);
            addr ^= __ZL8foldCaset(((unsigned short)(0xc000)));
            addr = __ZL8foldCaset_0(addr);

            if (addr >= (eom - buf)) {
                return ((32 + 100000) + 1);
            }
            status = get_name_len(depth + 1, buf, buf + addr, eom, &dummy,
                                  &nlen);
            if (status != 0) {
                return status;
            }
            *len += 2;
            *namelen += nlen;
            return 0;
        }


        label_len = (unsigned int)*p1 & 0xff;
        if (buf + label_len > eom) {
            return ((32 + 100000) + 1);
        }
        p1 += label_len + 1;
        *len += label_len + 1;
        if (*p1 != '\0') {
            label_len++;
        }
        *namelen += label_len;
        if (p1 >= eom) {
            return ((32 + 100000) + 9);
        }
    }
}