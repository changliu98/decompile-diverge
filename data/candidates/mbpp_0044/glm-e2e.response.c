const char* func0(const char* str) {
    const char* pattern = "^[A-Za-z0-9]+$";
    regex_t regex;
    const char* result;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        result = "Failed to compile regex";
    } else {
        int ret = regexec(&regex, str, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = "String matches";
        } else {
            result = "No match found";
        }
    }
    
    return result;
}