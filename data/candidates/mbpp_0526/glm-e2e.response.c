char *func0(const char *str) {
    size_t len = strlen(str);
    char *res = malloc(len + 1);
    
    if (res == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        res[0] = toupper(str[0]);
        
        for (size_t i = 1; i < len; i++) {
            res[i] = tolower(str[i]);
        }
        
        res[len - 1] = toupper(res[len - 1]);
        res[len] = '\0';
    }
    
    return res;
}