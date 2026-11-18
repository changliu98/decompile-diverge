const char* func0(const char* str) {
    int has_zero = 0;
    int has_one = 0;
    int has_other = 0;
    int i = 0;
    
    while (i < strlen(str)) {
        if (str[i] == '0') {
            has_zero = 1;
        } else if (str[i] == '1') {
            has_one = 1;
        } else {
            has_other = 1;
            break;
        }
        i++;
    }
    
    if ((has_zero || has_one) && !has_other) {
        return "Yes";
    } else {
        return "No";
    }
}