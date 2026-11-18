static int func0(char *s, struct tm *tm) {
    char *p;
    int ret;

    if (!s)
        ret = -1;

    while (1) {
        p = s;
        s = NULL;
        if (p) {
            if (p[0] == 'T' || p[0] == 't')
                ret = 1;
            else if (p[0] =='')
                ret = 0;
            else
                ret = -1;
        }
        if (ret == 0) {
            while (*p && *p!= 'T' && *p!= 't')
                p++;
            if (*p)
                ret = -1;
        }
        if (ret == 1) {
            if (*p == 'D' || *p == 'd')
                ret = -1;
        }
        if (ret == 0 || ret == 1) {
            p++;
            while (*p && *p!= '+' && *p!= '-')
                p++;
            if (*p)
                ret = -1;
        }
        if (ret == 0 || ret == 1) {
            p++;
            while (*p && *p!= 'Z' && *p!= 'z')
                p++;
            if (*p)
                ret = -1;
        }
        if (ret == 0 || ret == 1) {
            p++;
            while (*p && *p!= 'D' && *p!= 'd')
                p++;
            if (*p)
                ret = -1;
        }
        if (ret == 0 || ret == 1) {
            p++;
            while (*p && *p!= 'T' && *p!= 't')
                p++;
            if (*p)
                ret = -1;
        }
        if (ret == 0 || ret == 1) {
            p++;
            while (*p && *p!= 'Z' && *p!= 'z')
                p++;
            if (*p)
                ret = -1;
        }