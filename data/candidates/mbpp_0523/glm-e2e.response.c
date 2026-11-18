exact size might differ

char* func0(char* s) {
    int has_lower = 0;
    int has_upper = 0;
    int has_digit = 0;
    int has_special = 1; // Initialized to 1 but never updated in the loop
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        if (islower(s[i])) {
            has_lower = 1;
        }
        if (isupper(s[i])) {
            has_upper = 1;
        }
        if (isdigit(s[i])) {
            has_digit = 1;
        }
    }
    
    func0_result[0] = '\0';
    
    if (!has_lower) {
        strcat(func0_result, "Missing lowercase letter"); // String at 0x2004
    }
    if (!has_upper) {
        strcat(func0_result, "Missing uppercase letter"); // String at 0x202d
    }
    if (!has_digit) {
        strcat(func0_result, "Missing digit");            // String at 0x2056
    }
    if (len < 8) {
        strcat(func0_result, "Password too short");       // String at 0x2071
    }
    
    if (has_lower && has_upper && has_digit && len >= 8) {
        strcpy(func0_result, "OK");                       // String at 0x2094
    } else {
        int last_idx = strlen(func0_result) - 1;
        if (func0_result[last_idx] == ',') {
            func0_result[last_idx] = '\0';
        }
    }
    
    return func0_result;
}