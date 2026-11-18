int func0(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    // Allocate memory for the doubled string plus the null terminator
    char *doubled = (char *)malloc(2 * len2 + 1);
    
    for (int i = 0; i < len2; i++) {
        // Copy the suffix of s2 starting at index i
        strncpy(doubled, s2 + i, len2 - i);
        
        // Copy the prefix of s2 up to index i
        strncpy(doubled + len2 - i, s2, i);
        
        // Null-terminate the concatenated string
        doubled[len2] = '\0';
        
        // If s1 is found as a substring, return 1 (true)
        if (strstr(s1, doubled) != NULL) {
            free(doubled);
            return 1;
        }
    }
    
    free(doubled);
    return 0;
}