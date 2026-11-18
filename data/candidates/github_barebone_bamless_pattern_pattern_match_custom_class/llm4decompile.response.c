int pattern_match_custom_class(const char c,const char *pattern_ptr,const char *class_end)
{
    int sign = 1;
    if (*(++pattern_ptr) == '^') {
        sign = 0;
        pattern_ptr++;
    }
    while (pattern_ptr < class_end) {
        if (*pattern_ptr == '%') {
            pattern_ptr++;
            if (pattern_match_class(c,*pattern_ptr))
                return sign;
        }
        else if (pattern_ptr[1] == '-' && pattern_ptr+2 < class_end) {
            pattern_ptr += 2;
            if (c >= pattern_ptr[-2] && c <= pattern_ptr[0])
                return sign;
        }
        else if (*pattern_ptr == c)
            return sign;
        pattern_ptr++;
    }
    return !sign;
}