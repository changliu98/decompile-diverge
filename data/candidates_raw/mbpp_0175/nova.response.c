bool func0(char *s) {
    int i = -1;
    int j = 0;
    char stack[strlen(s)];
    while (1) {
        if (j >= strlen(s))
            break;
        char c = s[j];
        if (c == '(' || c == '{' || c == '[') {
            stack[++i] = c;
        } else {
            if (i == -1) {
                char tmp = '\0';
            } else {
                char tmp = stack[i--];
                if ((c == ')' && tmp == '(') || (c == '}' && tmp == '{') ||
                    (c == ']' && tmp == '[')) {
                } else {
                    char tmp = '\0';
                }
            }
        }
        j++;
    }
    bool result = (i == -1)? true : false;
    return result;
}