int is_bool_str(const char *s, int *ok) {
    int ret;

    if (s == NULL || ok == NULL) {
        *ok = 0;
        return 0;
    }

    if (strcmp(s, "0") == 0 || strcmp(s, "false") == 0) {
        *ok = 1;
        return 0;
    }

    if (strcmp(s, "1") == 0 || strcmp(s, "true") == 0) {
        *ok = 1;
        return 1;
    }

    if (strcmp(s, "yes") == 0 || strcmp(s, "on") == 0) {
        *ok = 1;
        return 1;
    }

    if (is_number(s)) {
        ret = atoi(s);
        *ok = ret!= 0;
        return ret;
    }

    if (is_float(s)) {
        double ret = atof(s);
        *ok = ret!= -0.0;
        return ret;
    }

    *ok = 0;
    return 0;
}