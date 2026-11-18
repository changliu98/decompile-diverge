char func0(void) {
    char c = getchar();
    char r;

    if (c)
        r = c;
    else {
        c = getchar();
        if (c)
            r = c;
        else
            r ='';
    }

    switch (r) {
    case '{':
    case '[':
    case '(':
        return r;
    case '}':
        return '{';
    case ']':
        return '[';
    case ')':
        return '(';
    default:
        return 0;
    }
}