int parse_width(const char *str, int *consumed) {
    int width = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            width = width * 10 + digit;
            i++;
        } else {
            break;
        }
    }
    
    *consumed = i;
    return width;
}