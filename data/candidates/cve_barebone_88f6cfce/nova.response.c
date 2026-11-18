void append_command(char *str) {
    char *p = str;
    char *q;
    fputs(str, stdout);
    q = (char *)malloc(sizeof(char) * (strlen(str) + strlen(str2)));
    while (1) {
        if (*p == '\0') {
            break;
        }
        if (strncmp(p, str1, strlen(str1)) == 0) {
            if (flag == 1) {
                if (*p == (char)0xc2 && *(p + 1) == (char)0xa0) {
                    p += (flag2 == 0)? 2 : 1;
                    strcpy(q, str3);
                    q += strlen(str3);
                } else {
                    if (flag3 == 1) {
                        strncpy(p, q, strlen(q));
                    } else {
                        *q++ = *p++;
                    }
                }
            } else {
                p++;
            }
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';
}