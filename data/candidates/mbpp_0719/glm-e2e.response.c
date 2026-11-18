const char* func0(const char* arg) {
    regex_t regex;
    int ret;
    const char* result;

    // Compile the regular expression
    // The pattern is located at 0x2004
    ret = regcomp(&regex, "^[A-Za-z]+$", REG_EXTENDED);
    
    if (ret != 0) {
        // If compilation fails, return the string at 0x2009
        result = "Invalid regex";
    } else {
        // Execute the regular expression
        ret = regexec(&regex, arg, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            // If it matches, return the string at 0x2022
            result = "Match";
        } else {
            // If it doesn't match, return the string at 0x2031
            result = "No match";
        }
    }
    
    return result;
}