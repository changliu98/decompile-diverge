static void ga_concat_shorten_esc(char *buf, char *p) {
    if (p == NULL)
        strcpy(buf, "");
    else {
        char *q = p;
        while (q!= NULL) {
            int n;
            char *r;
            if (*q == '\0')
                break;
            r = q;
            n = strlen(r);
            for (;;) {
                if (*r == '\0')
                    break;
                if (isspace(*r) == isspace(p[0])) {
                    n++;
                    r++;
                } else
                    break;
            }
            if (n > 20) {
                strcpy(buf, "...");
                strncat(buf, p, n);
                strcat(buf, "...");
                char tmp[200];
                snprintf(tmp, sizeof(tmp), "<a href=\"javascript:void(0)\" "
                                           "onclick=\"show_help('%s')\">...</a>",
                         tmp);
                strcat(buf, tmp);
                q = r - 1;
            } else
                strncpy(buf, r, n);
            q = r;
        }
    }
}