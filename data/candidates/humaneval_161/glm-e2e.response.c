char* func0(char *str) {
    int non_alpha_count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            if (islower(str[i])) {
                str[i] = tolower(str[i]);
            } else if (isupper(str[i])) {
                str[i] = toupper(str[i]);
            }
        } else {
            non_alpha_count++;
        }
    }
    
    if (non_alpha_count == len) {
        for (int i = 0; i < len / 2; i++) {
            char temp = str[i];
            str[i] = str[len - i - 1];
            str[len - i - 1] = temp;
        }
    }
    
    return str;
}