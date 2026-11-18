char *func0(char *arg) {
    regex_t regex;
    regmatch_t match;
    char pattern_str[5]; // Allocated 5 bytes to safely hold the pattern and null terminator
    char *result;
    char *current;

    // Load the pattern from the .rodata section.
    // The assembly loads 4 bytes into -0x55(%rbp) and 1 byte into -0x51(%rbp).
    // This corresponds to a 4-character string (e.g., " \n\t") plus the null terminator.
    pattern_str[0] = ' ';
    pattern_str[1] = '\n';
    pattern_str[2] = '\t';
    pattern_str[3] = ' '; // Adjust based on exact constants if known
    pattern_str[4] = '\0';

    result = (char *)malloc(strlen(arg) + 1);
    regcomp(&regex, pattern_str, 1); // REG_EXTENDED is typically 1
    strcpy(result, arg);

    current = result;
    while (regexec(&regex, current, 1, &match, 0) == 0) {
        size_t len = strlen(current);
        size_t start = match.rm_so;
        size_t end = match.rm_eo;

        memmove(current + start + 1, current + end, len - end + 1);
        current = current + start + 1;
    }

    regfree(&regex);
    return result;
}