bool pattern_match_custom_class(char c, const char *p, const char *end) {
    bool negate = true;
    
    // Check if the first character in the pattern is '^'
    if (p[1] == '^') {
        negate = false;
        p++;
    }
    
    while (1) {
        p++;
        if (p >= end) {
            return !negate;
        }
        
        if (*p == '%') {
            p++;
            // Call to an external function (e.g., checking escape sequences or custom classes)
            if (custom_char_match(c, *p)) {
                return negate;
            }
        } else if (p[1] == '-' && p + 2 < end) {
            p += 2;
            // Check if c is within the range [p[-2], p[0]]
            if (p[-2] <= c && c <= p[0]) {
                return negate;
            }
        } else {
            // Check if c matches the current character
            if (*p == c) {
                return negate;
            }
        }
    }
}