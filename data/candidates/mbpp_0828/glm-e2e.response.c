void func0(const char *str, int *spaces, int *digits, int *others) {
    *others = 0;
    *digits = 0;
    *spaces = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            (*spaces)++;
        } else if (isdigit(str[i])) {
            (*digits)++;
        } else {
            (*others)++;
        }
    }
}