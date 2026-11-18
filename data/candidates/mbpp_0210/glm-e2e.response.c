int func0(const char *str) {
    regex_t regex;
    int ret;

    // Compile the regular expression. 
    // The pattern is located at 0x2004 and has a length of 1 (e.g., ".").
    regcomp(&regex, ".", 1);

    // Execute the regular expression against the input string.
    // 0 is passed as eflags.
    ret = regexec(&regex, str, 0, NULL, 0);

    // Free the compiled regular expression.
    regfree(&regex);

    // Return 1 if regexec returned 1 (REG_NOMATCH), 0 otherwise.
    return ret == 1;
}