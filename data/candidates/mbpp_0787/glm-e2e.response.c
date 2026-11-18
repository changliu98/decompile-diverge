const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* result;

    const char* pattern = "^[A-Za-z]+$"; // Assuming this is the pattern at 0x2004

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Failed to compile regex\n"); // Assuming string at 0x200a
        result = "Error"; // Assuming string at 0x2023
    } else {
        ret = regexec(&regex, str, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = "Match"; // Assuming string at 0x203b
        } else {
            result = "No Match"; // Assuming string at 0x204a
        }
    }

    return result;
}