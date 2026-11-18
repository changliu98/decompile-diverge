const char* func0(const char* arg) {
    regex_t regex;
    int ret;
    const char* result;
    const char* match_str;

    // Compile the regular expression
    // The pattern is located at 0x2004, and the flags are 1 (REG_EXTENDED)
    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    
    if (ret != 0) {
        // regcomp failed, return error string at 0x2008
        result = "Invalid";
    } else {
        // Execute the regular expression
        // eflags is 0
        ret = regexec(&regex, arg, 0, NULL, 0);
        
        if (ret == 0) {
            // Matched successfully, return string at 0x2015
            match_str = "Valid";
        } else {
            // Did not match, return string at 0x2008
            match_str = "Invalid";
        }
        
        // Free the compiled regex
        regfree(&regex);
        result = match_str;
    }
    
    return result;
}