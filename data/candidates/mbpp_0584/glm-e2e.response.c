char *func0(const char *input) {
    regex_t regex;
    regmatch_t match;
    char matched_str[100];
    char *ret_val = NULL;

    if (regcomp(&regex, "^[a-zA-Z0-9]+$", 1) != 0) {
        printf("Failed to compile regex\n");
        ret_val = NULL;
    } else {
        if (regexec(&regex, input, 1, &match, 0) == 0) {
            int start = match.rm_so;
            int end = match.rm_eo;
            
            strncpy(matched_str, input + start, end - start);
            matched_str[end - start] = '\0';
            
            snprintf(result, 100, "Matched: %s, Start: %d, End: %d", matched_str, start, end);
            
            regfree(&regex);
            ret_val = result;
        } else {
            regfree(&regex);
            ret_val = NULL;
        }
    }
    
    return ret_val;
}