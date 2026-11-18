void str_rtrim(char *str, char trim)
{
    char *end = strchr(str, trim);
    if (end != NULL) {
        *end = '\0';
    }
}