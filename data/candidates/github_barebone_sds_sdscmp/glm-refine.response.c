int __cdecl sdscmp(const sds s1, const sds s2) {
    size_t l1 = sdslen(s1);
    size_t l2 = sdslen(s2);
    
    // Compare up to the length of the shorter string
    size_t min_len = (l1 < l2) ? l1 : l2;
    int cmp = memcmp(s1, s2, min_len);
    
    // If they differ within the minimum length, return the difference
    if (cmp != 0) {
        return cmp;
    }
    
    // If they match up to the minimum length, the longer string is considered greater
    if (l1 > l2) {
        return 1;
    } else if (l1 < l2) {
        return -1;
    }
    
    // Strings are completely identical in content and length
    return 0;
}