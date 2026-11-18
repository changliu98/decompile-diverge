int parse_matrix_header(char *s, int *x, int *y, double *t, double *dt) {
    char *p;
    int i;
    double tt, dt2;
    char *tstr;

    p = strchr(s, '\r');
    if (p == NULL)
        p = strchr(s, '\n');
    *p = '\0';

    for (i = 0;; i++) {
        tstr = strtok(s, ",");
        if (tstr == NULL)
            break;
        if (i < 4)
            continue;
        if (sscanf(tstr, "%d", x + i)!= 0) {
            sprintf(errstr, "parse_matrix_header: x[%d] = %s", i, tstr);
            return -1;
        }
    }

    if (*x > 0 && *x > NX) {
        sprintf(errstr, "parse_matrix_header: x = %d", *x);
        return -1;
    }
    if (*y > 0 && *y > NY) {
        sprintf(errstr, "parse_matrix_header: y = %d", *y);
        return -1;
    }

    if (i < 4) {
        tt = 0.0;
        dt2 = -1.0;
    } else {
        tt = tstr[0] == '\0'? -1.0 : atof(tstr);
        dt2 = tstr[0] == '\0'? -1.0 : atof(tstr + 1);
    }

    *t = tt;
    *dt = dt2;

    return 0;
}