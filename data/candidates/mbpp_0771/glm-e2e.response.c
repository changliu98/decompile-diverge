bool func0(const char *str) {
    int len = strlen(str);
    if (len % 2 != 0) {
        return false;
    }

    char stack[128];
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                return false;
            }
            char open = stack[top--];
            if ((open == '(' && c != ')') ||
                (open == '{' && c != '}') ||
                (open == '[' && c != ']')) {
                return false;
            }
        }
    }

    return top == -1;
}