int parse_matrix_header(char *str, int *out_width, int *out_height, double *out_scale, double *out_offset) {
    double values[4];
    int count = 0;
    char *p;
    char *token;
    int ret = -1;

    // Strip carriage return or newline
    p = strchr(str, '\r');
    if (!p) {
        p = strchr(str, '\n');
    }
    if (p) {
        *p = '\0';
    }

    p = str;

    // Parse up to 4 double values from the string
    while ((token = vips_break_token(p, " \t")) != NULL && count < 4) {
        if (vips_strtod(p, &values[count]) != 0) {
            vips_error("matrix", "%s", "bad number");
            return -1;
        }
        count++;
        p = token;
    }

    // Default values for scale and offset if not provided
    if (count < 4) {
        values[3] = 0.0; // offset
    }
    if (count < 3) {
        values[2] = 1.0; // scale
    }
    if (count < 2) {
        vips_error("matrix", "%s", "bad size");
        return -1;
    }

    // Check that width and height are integers
    if (floor(values[0]) != values[0] || floor(values[1]) != values[1]) {
        vips_error("matrix", "%s", "bad dimensions");
        return -1;
    }

    *out_width = (int)values[0];
    *out_height = (int)values[1];

    // Validate width and height bounds
    if (*out_width <= 0 || *out_width > 100000 || 
        *out_height <= 0 || *out_height > 100000) {
        vips_error("matrix", "%s", "bad dimensions");
        return -1;
    }

    // Scale must not be zero
    if (values[2] == 0.0) {
        vips_error("matrix", "%s", "bad scale");
        return -1;
    }

    *out_scale = values[2];
    *out_offset = values[3];

    return 0;
}