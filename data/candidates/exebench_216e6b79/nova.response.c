void unescape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[j]!= '\0') {
        switch (t[j]) {
        case '\\':
            switch (t[j + 1]) {
            case 'n':
                s[i] = '\n';
                break;
            case 't':
                s[i] = '\t';
                break;
            case 'r':
                s[i] = '\r';
                break;
            case 'b':
                s[i] = '\b';
                break;
            case 'f':
                s[i] = '\f';
                break;
            case 'v':
                s[i] = '\v';
                break;
            case 'a':
                s[i] = '\a';
                break;
            case '\\':
                s[i] = '\\';
                break;
            case '\'':
                s[i] = '\'';
                break;
            case '"':
                s[i] = '"';
                break;
            default:
                s[i] = t[j];
                break;
            }
            j++;
            break;
        default:
            s[i] = t[j];
            break;
        }
        i++;
        j++;
    }
    s[i] = '\0';
}