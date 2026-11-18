void func0(const char *str, int *digits, int *spaces) {
    int digit_count = 0;
    int space_count = 0;
    
    while (*str != '\0') {
        if (isspace(*str)) {
            space_count++;
        } else if (isdigit(*str)) {
            digit_count++;
        }
        str++;
    }
    
    *digits = digit_count;
    *spaces = space_count;
}