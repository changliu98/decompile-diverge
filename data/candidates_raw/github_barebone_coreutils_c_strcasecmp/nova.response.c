int func0(const char *s1, const char *s2) {
    const unsigned char *us1 = (const unsigned char *)s1,
                        *us2 = (const unsigned char *)s2;
    int delta = 0;

    
    if (us1 == us2) return 0;

    while (1) {
        unsigned char u1 = *us1, u2 = *us2;

        if (u1!= u2) {
            delta = u1 - u2;
            break;
        } else if (u1 == 0) { 
            break;
        }
        us1++;
        us2++;
    }
    return delta;
}