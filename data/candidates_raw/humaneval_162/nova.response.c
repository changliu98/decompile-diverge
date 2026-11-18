char *func0(char *s) {
    char *p;
    unsigned int h;
    int i, j;

    if (strlen(s) == 0)
        return strdup("-1");
    h = -1;
    for (i = 0;;) {
        if (s[i]!= 0) {
            char c = s[i];
            h = h ^ c;
            for (j = 0; j < 8; j++) {
                if (h & 1)
                    h = (h >> 1) ^ 0xEDB88320UL;
                else
                    h = h >> 1;
            }
        } else {
            h = ~h;
            break;
        }
        i++;
    }
    p = (char *)malloc(9);
    if (p!= NULL)
        sprintf(p, "%08x", h);
    return p;
}