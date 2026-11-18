static int is_bool_str(char *s, int *b)
{
    int rc;

    if (!s || !b) {
        rc = 0;
        goto exit;
    }

    if (strcasecmp(s, "true") == 0) {
        goto loc_true;
    } else if (strcasecmp(s, "yes") == 0) {
        goto loc_true;
    } else if (strcasecmp(s, "on") == 0) {
        goto loc_true;
    } else if (strcasecmp(s, "false") == 0) {
        goto loc_false;
    } else if (strcasecmp(s, "no") == 0) {
        goto loc_false;
    } else if (strcasecmp(s, "off") == 0) {
        goto loc_false;
    } else if (is_integer(s)) {
        int64_t i = atoi64(s);
        *b = (i != 0) ? 1 : 0;
        rc = 1;
        goto exit;
    } else if (is_float(s)) {
        double d = atof(s);
        *b = (d != 0.0) ? 1 : 0;
        rc = 1;
        goto exit;
    }

    goto loc_error;

loc_true:
    *b = 1;
    rc = 1;
    goto exit;

loc_false:
    *b = 0;
    rc = 1;

exit:
    return rc;

loc_error:
    rc = 0;
    goto exit;
}