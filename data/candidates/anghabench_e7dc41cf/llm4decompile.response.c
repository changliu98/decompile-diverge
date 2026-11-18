int issymbol(char c)
{
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '>':
    case '<':
    case '[':
    case ']':
    case '{':
    case '}':
    case '(':
    case ')':
    case ',':
    case '%':
    case ' ':
        return 1;
    default:
        return 0;
    }
}