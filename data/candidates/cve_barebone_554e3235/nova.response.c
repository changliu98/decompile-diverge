int parse_matrix_header(char *str, int *x, int *y, double *t, double *dt) {
    char *p;
    int i;
    double tt, dt2;
    char *p2;

    p = strchr(str, '\r');
    if (p == NULL)
        p = strchr(str, '\n');
    *p = '\0';

    i = 0;
    for (;;) {
        p = str;
        p2 = strstr(p, "t=");
        if (p2!= NULL) {
            if (i > 4)
                break;
            sscanf(p2, "t=%lf", &tt);
            i++;
        }
        p = p2;
        p2 = strstr(p, "dt=");
        if (p2!= NULL) {
            if (i > 3)
                break;
            sscanf(p2, "dt=%lf", &dt2);
            i++;
        }
        p = p2;
        p2 = strstr(p, "x=");
        if (p2!= NULL) {
            if (i > 1)
                break;
            sscanf(p2, "x=%d", x);
            i++;
        }
        p = p2;
        p2 = strstr(p, "y=");
        if (p2!= NULL) {
            if (i > 2)
                break;
            sscanf(p2, "y=%d", y);
            i++;
        }
        p = p2;
        if (i == 4)
            break;
    }
    if (dt2 == 0.0) {
        *t = tt;
        *dt = dt2;
        i = 0;
    }
    return i;
}