char *gf_text_get_utf8_line(char *buf, int size, void *fp, int mode) {
    char tmp[2048];
    char *p;
    int i, j, len;
    char *ret;

    memset(buf, 0, size);
    ret = gf_fgets(buf, size, fp);
    if (ret == NULL) {
        return NULL;
    }

    if (mode <= 1) {
        j = 0;
        len = strlen(buf);
        i = 0;
        while (i < len) {
            if (mode != 0 || (buf[i] & 0x80) == 0) {
                tmp[j++] = buf[i];
                if (j >= 0x7ff) {
                    break;
                }
                i++;
            } else {
                if ((buf[i + 1] & 0xc0) != 0x80) {
                    tmp[j++] = (buf[i] >> 6) | 0xc0;
                    buf[i] &= 0xbf;
                    tmp[j++] = buf[i];
                    if (j >= 0x7ff) {
                        break;
                    }
                    i++;
                } else {
                    if ((buf[i] & 0xe0) == 0xc0) {
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                    } else if ((buf[i] & 0xf0) == 0xe0) {
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                    } else if ((buf[i] & 0xf8) == 0xf0) {
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                        tmp[j++] = buf[i++];
                    } else {
                        i++;
                    }
                    if (j >= 0x7ff) {
                        break;
                    }
                }
            }
        }
        tmp[j] = 0;
        strcpy(buf, tmp);
        return ret;
    } else if (mode == 2) {
        i = 0;
        while (buf[i] != 0 || buf[i + 1] != 0) {
            char c = buf[i + 1];
            buf[i + 1] = buf[i];
            buf[i] = c;
            i += 2;
        }
    }

    p = buf;
    i = gf_utf8_wcstombs(tmp, 0x800, &p);
    if (i == -1) {
        i = 0;
    }
    tmp[i] = 0;
    strcpy(buf, tmp);

    if (mode == 3) {
        gf_fgetc(fp);
    }

    return ret;
}