char *gf_text_get_utf8_line(char *buf, int size, void *stream, int mode) {
    char tmp[2048];
    char *res;
    int len, i, j;
    unsigned char c1, c2;

    memset(buf, 0, size);
    res = gf_fgets(buf, size, stream);
    if (res == NULL) {
        return NULL;
    }

    if (mode <= 1) {
        j = 0;
        len = strlen(buf);
        i = 0;
        while (i < len) {
            if (mode == 0) {
                if ((buf[i] & 0x80) != 0) {
                    if ((buf[i + 1] & 0xC0) != 0x80) {
                        if (j >= 2048) break;
                        tmp[j] = (buf[i] >> 6) | 0xC0;
                        j++;
                        buf[i] &= 0xBF;
                    } else if ((buf[i] & 0xE0) == 0xC0) {
                        if (j >= 2048) break;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                    } else if ((buf[i] & 0xF0) == 0xE0) {
                        if (j + 1 >= 2048) break;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                    } else if ((buf[i] & 0xF8) == 0xF0) {
                        if (j + 2 >= 2048) break;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                        tmp[j] = buf[i];
                        i++;
                        j++;
                    } else {
                        i++;
                        continue;
                    }
                }
            }
            if (j >= 2048) break;
            tmp[j] = buf[i];
            j++;
            i++;
        }
        if (j >= 2048) {
            j = 2047;
        }
        tmp[j] = 0;
        strcpy(buf, tmp);
        return res;
    } else if (mode == 2) {
        i = 0;
        while (buf[i] != 0 || buf[i + 1] != 0) {
            c1 = buf[i + 1];
            c2 = buf[i];
            buf[i + 1] = c2;
            buf[i] = c1;
            i += 2;
        }
    }

    char *p = buf;
    i = gf_utf8_wcstombs(tmp, 2048, &p);
    if (i == -1) {
        i = 0;
    }
    tmp[i] = 0;
    strcpy(buf, tmp);

    if (mode == 3) {
        gf_fgetc(stream);
    }

    return res;
}