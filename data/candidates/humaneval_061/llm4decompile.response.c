int func0(char *brackets)
{
    int i = 0;
    int level = 0;
    while (i < strlen(brackets)) {
        if (brackets[i] == '(') {
            level++;
        }
        if (brackets[i] == ')') {
            level--;
        }
        if (level < 0) {
            return 0;
        }
        i++;
    }
    return level == 0;
}