char* convert_set_sign(char* str, int* sign) {
    *sign = 1;
    if (str != NULL) {
        if (*str == '+') {
            *sign = 1;
            str++;
        } else if (*str == '-') {
            *sign = -1;
            str++;
        }
    }
    return str;
}