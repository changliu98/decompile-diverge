int parse_matrix_header(char *line, int *width, int *height, double *scale, double *offset)
{
    char *s = line;
    char *t;
    char *s1;
    char *s2;
    double header[4];
    int i;
    s1 = strstr(s, "\r");
    if (!s1)
        s1 = strstr(s, "\n");
    if (s1)
        *s1 = '\0';
    i = 0;
    s2 = s;
    s = strword(s, ' ');
    while (s && i < 4) {
        if (atofword(s2, &header[i])) {
            err_at("matload", "bad number \"%s\"", s2);
            return -1;
        }
        i++;
        s2 = s;
        s = strword(s, ' ');
    }
    if (i < 4)
        header[3] = 0.0;
    if (i < 3)
        header[2] = 1.0;
    if (i < 2) {
        err_at("matload", "%s", "no width / height");
        return -1;
    }
    if (isint(header[0]) && isint(header[1])) {
        *width = (int)header[0];
        *height = (int)header[1];
        if (*width < 1 || *width > 100000 || *height < 1 || *height > 100000) {
            err_at("mask2vips", "%s", "width / height out of range");
            return -1;
        }
        if (header[2] == 0.0) {
            err_at("mask2vips", "%s", "zero scale");
            return -1;
        }
        *scale = header[2];
        *offset = header[3];
        return 0;
    }
    err_at("mask2vips", "%s", "width / height not int");
    return -1;
}