static int json_get_escape_len(char *str, int len)
{
    int ret;
    int i;

    switch (*str) {
    case 'u':
        if (len < 7) {
            ret = -2;
        } else {
            char valid = 1;
            if (!json_isxdigit(str[1]))
                valid = 0;
            if (!json_isxdigit(str[2]))
                valid = 0;
            if (!json_isxdigit(str[3]))
                valid = 0;
            if (!json_isxdigit(str[4]))
                valid = 0;
            ret = valid ? 5 : -1;
        }
        break;
    case '"':
    case '\\':
    case '/':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
        ret = (len >= 3) ? 1 : -2;
        break;
    default:
        ret = -1;
    }

    return ret;
}