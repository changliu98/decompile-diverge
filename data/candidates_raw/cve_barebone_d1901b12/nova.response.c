int func0(FILE *fp, char *name, int len, int type, int size, int namelen,
          char *buf) {
    int i, ret;
    char tmp[10];

    if (size == sizeof(struct stat) &&
        strncmp(name + len, "/./", 3) == 0) {
        if (namelen < 5 || namelen > 20)
            return 1;
        *fp->_p = *fp->_p | 0x10;
        size = namelen;
        switch (namelen) {
        case 8:
            strcpy(tmp, "..2612/");
            break;
        case 16:
            strcpy(tmp, "..5224/");
            break;
        case 20:
            strcpy(tmp, "..7836/");
            break;
        default:
            strcpy(tmp, "..0410/");
            break;
        }
        if (fprintf(fp, tmp) == -1)
            ret = 1;
        else {
            memcpy(buf, name + len, namelen);
            for (i = 0; i < namelen; i++) {
                if (fprintf(fp, "%02x", buf[i]) == -1)
                    ret = 1;
            }
        }
    } else
        ret = 1;
    return ret;
}