bool func0(char *str) {
    bool is_letter = false;
    bool is_digit = false;
    while (*str) {
        if (isalpha(*str))
            is_letter = true;
        if (isdigit(*str))
            is_digit = true;
        str++;
    }
    bool is_special = is_letter && is_digit;
    return is_special;
}