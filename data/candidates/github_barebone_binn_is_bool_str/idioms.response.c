int is_bool_str(char *str, _Bool *out)
{
    if (str == ((void *)0) || out == ((void *)0))
        return 0;
    if (strcasecmp(str, "true") == 0 ||
        strcasecmp(str, "yes") == 0 ||
        strcasecmp(str, "on") == 0) {
        *out = 1;
        return 1;
    }
    if (strcasecmp(str, "false") == 0 ||
        strcasecmp(str, "no") == 0 ||
        strcasecmp(str, "off") == 0) {
        *out = 0;
        return 1;
    }
    if (is_integer(str)) {
        *out = (atoi64(str) != 0);
        return 1;
    }
    if (is_float(str)) {
        *out = (atof(str) != 0);
        return 1;
    }
    return 0;
}