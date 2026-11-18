const char* func0(const char* arg) {
    regex_t regex;
    int ret;
    const char* result;

    const char* pattern = "^[A-Z][a-z]*$"; // Extracted from the string literal at 0x2004
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    
    if (ret != 0) {
        fprintf(stderr, "Regex compilation failed\n"); // Extracted from 0x200b
        result = "Compilation error"; // Extracted from 0x2024
    } else {
        ret = regexec(&regex, arg, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = "Match"; // Extracted from 0x202a
        } else {
            result = "No match"; // Extracted from 0x2039
        }
    }
    
    return result;
}