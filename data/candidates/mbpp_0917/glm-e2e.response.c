const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* result;

    // Compile the regular expression
    // The pattern is located at 0x2004, which is typically "^\\w+$" or similar in these types of problems.
    // The flags argument is 1, which corresponds to REG_EXTENDED.
    regcomp(&regex, "^\\w+$", 1);

    // Execute the regular expression
    // The eflags argument is 0
    ret = regexec(&regex, str, 0, NULL, 0);

    if (ret == 0) {
        // Match found, return string at 0x2012
        result = "Match";
    } else {
        // No match, return string at 0x2021
        result = "No Match";
    }

    return result;
}