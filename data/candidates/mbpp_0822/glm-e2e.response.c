int func0(const char *str) {
    int len = strlen(str);
    _Bool has_upper = 0;
    _Bool has_lower = 0;
    _Bool has_digit = 0;
    _Bool has_special = 0;
    _Bool result = 0;

    if (len < 6 || len > 12) {
        result = 0;
    } else {
        for (int i = 0; i < len; i++) {
            if (isupper(str[i])) {
                has_upper = 1;
            } else if (islower(str[i])) {
                has_lower = 1;
            } else if (isdigit(str[i])) {
                has_digit = 1;
            } else if (str[i] == '$' || str[i] == '#' || str[i] == '@') {
                has_special = 1;
            } else if (isgraph(str[i])) {
                result = 0;
                break;
            }
        }
        if (!result) {
            result = has_upper && has_lower && has_digit && has_special;
        }
    }
    
    return result;
}