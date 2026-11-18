void msg_puts_printf(char *s, int n) {
    char *p = s;
    char *q = NULL;
    int len;

    while (1) {
        if (n < 0 || n > (int)(s - p))
            q = NULL;
        else
            q = strnchr(p, n);
        if (q) {
            if (verbose)
                printf("%.*s\n", (int)(q - p), p);
            if (p!= q)
                add_line(p, q);
            p = q + 1;
        } else {
            if (p!= s && *p!= '\0')
                add_line(p, NULL);
            break;
        }
        if (verbose)
            printf("--\n");
    }
    if (p!= NULL)
        add_line(p, NULL);
}