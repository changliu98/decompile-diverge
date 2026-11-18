int memcasecmp(const void *s1, const void *s2, unsigned long n) {
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    unsigned long i = 0;
    int diff = 0;

    while (i < n) {
        unsigned char c1 = p1[i];
        unsigned char c2 = p2[i];
        
        int u1 = toupper(c1);
        int u2 = toupper(c2);
        
        diff = u1 - u2;
        if (diff != 0) {
            return diff;
        }
        i++;
    }
    
    return 0;
}