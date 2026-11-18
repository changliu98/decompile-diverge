char *func0(const char *s) {
    int len = strlen(s);
    char *res = malloc(len * 2 + 1);
    
    if (!res) {
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        int is_palindrome = 1;
        for (int j = 0; j < (len - i) / 2; j++) {
            if (s[i + j] != s[len - 1 - j]) {
                is_palindrome = 0;
                break;
            }
        }
        
        if (is_palindrome) {
            strncpy(res, s, len);
            for (int j = 0; j < i; j++) {
                res[len + j] = s[i - j - 1];
            }
            res[len + i] = '\0';
            return res;
        }
    }

    strncpy(res, s, len);
    for (int j = 0; j < len; j++) {
        res[len + j] = s[len - j - 1];
    }
    res[len * 2] = '\0';
    
    return res;
}