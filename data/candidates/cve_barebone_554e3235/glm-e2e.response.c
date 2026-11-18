int parse_matrix_header(char *str, int *out_width, int *out_height, double *out_scale, double *out_offset) {
    char *p;
    char *token;
    int n_tokens = 0;
    double values[4] = {0.0, 0.0, 0.0, 0.0};
    int ret = -1;

    // Strip carriage return or newline
    p = strchr(str, '\r');
    if (p == NULL) {
        p = strchr(str, '\n');
    }
    if (p != NULL) {
        *p = '\0';
    }

    p = str;
    while ((token = vips_break_token(p, " ")) != NULL && n_tokens < 4) {
        if (vips_strtod(p, &values[n_tokens]) != 0) {
            vips_error("matrix", "%s", "unable to parse number");
            return -1;
        }
        n_tokens++;
        p = token;
    }

    if (n_tokens < 4) {
        values[3] = 0.0;
    }
    if (n_tokens < 3) {
        values[2] = 1.0;
    }
    if (n_tokens < 2) {
        vips_error("matrix", "%s", "%s");
        return -1;
    }

    if (floor(values[0]) != values[0] || floor(values[1]) != values[1]) {
        vips_error("matrix", "%s", "dimensions must be integers");
        return -1;
    }

    *out_width = (int)values[0];
    *out_height = (int)values[1];

    if (*out_width <= 0 || *out_width > 100000 || *out_height <= 0 || *out_height > 100000) {
        vips_error("matrix", "%s", "dimensions out of range");
        return -1;
    }

    if (values[2] == 0.0) {
        vips_error("matrix", "%s", "scale must be non-zero");
        return -1;
    }

    *out_scale = values[2];
    *out_offset = values[3];

    return 0;
}