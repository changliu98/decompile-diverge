bool func0(char *s) {
    int len = strlen(s);
    if (len % 2!= 0)
        return false;
    char stack[101];
    int top = -1;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                return false;
            }
            char t = stack[top--];
            if (t == '(' && c!= ')')
                return false;
            if (t == '{' && c!= '}')
                return false;
            if (t == '[' && c!= ']')
                return false;
        }
    }
    return top % 2 == 0;
}