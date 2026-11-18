const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* result;

    // Compile the regular expression
    // The pattern is located at 0x2004
    ret = regcomp(&regex, "^[A-Za-z]+$", REG_EXTENDED);
    
    if (ret != 0) {
        // Pattern at 0x200b
        result = "Invalid regex";
    } else {
        // Execute the regular expression
        ret = regexec(&regex, str, 0, NULL, 0);
        
        if (ret == 0) {
            // Pattern at 0x2025
            result = "Match";
        } else if (ret == 1) {
            // Pattern at 0x2034
            result = "No match";
        } else {
            // Pattern at 0x2041
            result = "Regex execution error";
        }
        
        regfree(&regex);
    }
    
    return result;
}