static bool pattern_match_custom_class(char c, const char* pattern_ptr, const char* class_end) {
    bool ret = true;
    if(pattern_ptr[1] == '^') {
        ret = false;
        pattern_ptr++;
    }

    while(++pattern_ptr < class_end) {
        if(*pattern_ptr == PATTERN_ESCAPE) {
            pattern_ptr++;
            if(pattern_match_class(c, *pattern_ptr)) {
                return ret;
            }
        } else if(pattern_ptr[1] == '-' && pattern_ptr + 2 < class_end) {
            pattern_ptr += 2;
            if(pattern_ptr[-2] <= c && c <= *pattern_ptr) {
                return ret;
            }
        } else if(*pattern_ptr == c) {
            return ret;
        }
    }

    return !ret;
}