char* func0(const char* input_str, const char* pattern_str) {
    char regex_pattern[10];
    regex_t regex;
    regmatch_t match;
    long long offset = 0;
    char* result = NULL;

    // Format the pattern string (e.g., "[%s]")
    sprintf(regex_pattern, "[%s]", pattern_str);

    // Compile the regular expression
    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    // Duplicate the input string so we can modify it
    char* str = strdup(input_str);
    if (!str) {
        regfree(&regex);
        return NULL;
    }

    // Loop to find and remove all matching characters
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        long long match_start = offset + match.rm_so;
        long long dest = str + match_start + 1;
        long long src = str + match_start + match.rm_eo;
        
        // Calculate the number of remaining bytes to shift down
        long long total_len = strlen(str);
        long long count = total_len - match_start - match.rm_so + match.rm_eo + 1;
        
        // Shift the rest of the string leftwards to overwrite the matched character
        memmove((void*)dest, (void*)src, count);
        
        // Advance offset just past the removed character
        offset = match_start + 1;
    }

    regfree(&regex);
    return str;
}