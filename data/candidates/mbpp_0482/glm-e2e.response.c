const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* result;

    // Compile the regular expression
    // The pattern is located at 0x2004, which is typically "^" or a similar simple pattern.
    // Based on the offsets, it's a string literal.
    regcomp(&regex, "^[A-Z][a-z]*$", REG_EXTENDED);

    // Execute the regular expression
    ret = regexec(&regex, str, 0, NULL, 0);

    // Free the compiled regular expression
    regfree(&regex);

    // Check the result
    if (ret == 0) {
        // Match found
        result = "Yes"; // Located at 0x2012
    } else {
        // No match
        result = "No";  // Located at 0x2016
    }

    return result;
}