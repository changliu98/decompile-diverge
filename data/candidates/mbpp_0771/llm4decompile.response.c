int func0(char *exp)
{
    int i, len = strlen(exp);
    char stack[100];
    int top = -1;
    char ch, open_ch;

    if (len % 2 != 0)
        return 0;

    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1)
                return 0;
            open_ch = stack[top--];
            if (open_ch == '(' && ch != ')')
                return 0;
            if (open_ch == '{' && ch != '}')
                return 0;
            if (open_ch == '[' && ch != ']')
                return 0;
        }
    }

    if (top != -1)
        return 0;

    return 1;
}