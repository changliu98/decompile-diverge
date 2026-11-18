int json_get_escape_len(const char *s, int len)
{
    int n;

    switch (*s) {
    case '\\':
    case '/':
    case '"':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
        n = 1;
        break;
    case 'u':
        if (len < 6) {
            n = -2;
            break;
        }
        if (!json_isxdigit(s[1]) || !json_isxdigit(s[2]) ||
            !json_isxdigit(s[3]) || !json_isxdigit(s[4])) {
            n = -1;
            break;
        }
        n = 5;
        break;
    default:
        n = -1;
        break;
    }

    if (n < 0) {
        return n;
    }

    if (len < n + 1) {
        return -2;
    }

    return n;
}