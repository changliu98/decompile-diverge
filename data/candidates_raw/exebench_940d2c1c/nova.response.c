void func0(char s[], char t[]) {
    int i, j;
    int c;

    i = j = 0;
    while ((c = t[i++])!= '\0') {
        switch (c) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\\':
            s[j++] = '\\';
            s[j++] = '\\';
            break;
        case '\"':
            s[j++] = '\\';
            s[j++] = '\"';
            break;
        default:
            s[j++] = t[i - 1];
            break;
        }
    }
    s[j] = t[i];
}