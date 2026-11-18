void func0(char s[], char t[]) {
    int i, j, c;
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
        default:
            s[j++] = c;
            break;
        }
    }
    s[j] = '\0';
}