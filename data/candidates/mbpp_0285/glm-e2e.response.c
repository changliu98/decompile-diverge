const char* func0(const char* str) {
    regex_t regex;
    const char* pattern = "^[A-Z][a-z]*$"; // Assuming this is the pattern at 0x2004
    const char* result;

    if (regcomp(&regex, pattern, 1) == 0) { // 1 corresponds to REG_EXTENDED
        int ret = regexec(&regex, str, 0, NULL, 0);
        if (ret == 0) {
            result = "Yes"; // Assuming this is the string at 0x200c
        } else {
            result = "No";  // Assuming this is the string at 0x201b
        }
        regfree(&regex);
    }
    
    return result;
}