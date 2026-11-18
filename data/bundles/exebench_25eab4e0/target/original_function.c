int substitute(char *data, char from, char to)
{
    char *c = NULL;

    c = data;
    while((c = strchr(c, from)) != NULL) {
        *(c++) = to;
    }

    return 1;
}