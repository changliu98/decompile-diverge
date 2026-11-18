int matload(char *line, int *width, int *height, double *scale, double *offset)
{
    char *s = line;
    int i;
    char *t; char *last;
    double header[4];
    last = strstr(s, "\r");
    if (!last)
        last = strstr(s, "\n");
    if (last)
        *last = '\0';
    for (i = 0, last = s; (t = strsep(&last, " \t")) != ((void *)0); i++) {
        if (i >= 4)
            break;
        if (isnum(last, &header[i]) != 0) {
            errout("matload", "bad number \"%s\"", last);
            return -1;
        }
    }
    if (i < 4)
        header[3] = 0.0;
    if (i < 3)
        header[2] = 1.0;
    if (i < 2) {
        errout("matload", "%s", "no width / height");
        return -1;
    }
    if (isint(header[0]) != header[0] || isint(header[1]) != header[1]) {
        errout("matload", "%s", "width / height not int");
        return -1;
    }
    if ((int)header[0] <= 0 || (int)header[0] > 100000
        || (int)header[1] <= 0 || (int)header[1] > 100000) {
        errout("matload", "%s", "width / height out of range");
        return -1;
    }
    if (header[2] == 0.0) {
        errout("mask2vips", "%s", "zero scale");
        return -1;
    }
    *width = (int)header[0];
    *height = (int)header[1];
    *scale = header[2];
    *offset = header[3];
    return 0;
}