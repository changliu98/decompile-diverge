int sdscmp(const char *s1, const char *s2) {
    size_t l1 = sdslen(s1);
    size_t l2 = sdslen(s2);
    
    // Determine the minimum length of the two strings
    size_t min_len = (l1 < l2) ? l1 : l2;
    
    // Compare the strings up to the minimum length
    int cmp = memcmp(s1, s2, min_len);
    
    if (cmp == 0) {
        // If the contents are the same up to min_len, the longer string is greater
        if (l1 > l2) {
            return 1;
        } else if (l1 < l2) {
            return -1;
        } else {
            return 0;
        }
    } else {
        // If the contents differ, return the result of memcmp
        return cmp;
    }
}