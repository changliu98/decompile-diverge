void func0(const char *src, char *dst) {
    regex_t regex;
    regmatch_t matches[3];
    char buffer[0x400];
    char *ptr;

    // Compile the regular expression.
    // The pattern is located at 0x2004. Based on the usage and offsets, 
    // it is highly likely to be a regex matching a word and its trailing spaces, 
    // such as "([^ ]* +)".
    regcomp(&regex, "([^ ]* +)", 1);

    // Copy the input string to a local buffer to safely modify it
    strcpy(buffer, src);
    ptr = buffer;

    // Initialize the destination string as empty
    dst[0] = '\0';

    // Loop to find all regex matches
    while (regexec(&regex, ptr, 3, matches, 0) == 0) {
        // Append the matched substring (e.g., word + spaces) to the destination
        strncat(dst, ptr, matches[0].rm_eo);
        
        // Append a comma
        strcat(dst, ",");

        // Advance the pointer past the matched portion
        ptr += matches[0].rm_eo;
    }

    // Append any remaining part of the string that didn't match the regex
    strcat(dst, ptr);

    // Free the compiled regex
    regfree(&regex);
}