static char *smb_fdata(regex_t *preg, char *text, char *p, char *e, int cflags) {
    char *t;
    size_t nmatch = 1;
    regmatch_t pmatch[1];

    while (1) {
        if (*p) {
            switch (*p) {
            case '*':
                p++;
                break;
            case '|':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case '(':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case ')':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case '[':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case ']':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case '-':
                p++;
                if (text < e) {
                    t = text;
                    text = NULL;
                }
                break;
            case '\\':
                p++;
                break;
            default:
                p++;
                break;
            }
        } else {
            if (text < e) {
                t = text;
                text = NULL;
            }
            break;
        }

        if (text == NULL) {
            text = t;
            continue;
        }

        if (regcomp(preg, p, REG_EXTENDED | REG_NOSUB) == 0) {
            if (regexec(preg, p, nmatch, pmatch, cflags) == 0) {
                t = text;
                text = NULL;
            } else {
                text = t;
            }
            regfree(preg);
        } else {