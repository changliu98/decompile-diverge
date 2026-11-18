int wc_match_inner(const char *pat, const char *str, const char *str_end) {
    // If the pattern starts with '*', try to match the rest of the pattern 
    // against the current string position first.
    if (*pat == '*') {
        int ret = wc_match_inner(pat, str, str_end);
        if (ret <= 0) {
            return ret;
        }
    }

    // Main matching loop
    while (*pat != '\0') {
        // Collapse consecutive '*' characters in the pattern
        while (*pat == '*') {
            pat++;
        }

        // If the pattern ends after '*', it matches the rest of the string
        if (*pat == '\0') {
            return 1;
        }

        // Try to find the next matching fragment
        int match_len = 0;
        while (*str != '\0') {
            const char *saved_pat = pat;
            const char *saved_str = str;

            match_len = wc_match_fragment(&pat, &str, str_end);
            
            // If an error occurred (negative), propagate it
            if (match_len < 0) {
                return match_len;
            }

            // If a match was found but the pattern is fully consumed and 
            // the string hasn't reached the end, we need to backtrack.
            if (match_len > 0 && *pat == '\0' && str != str_end) {
                // Restore pointers to retry matching from the next character
                str = str_end - (str - saved_str);
                pat = saved_pat;
                
                return wc_match_inner(&pat, &str, str_end);
            }

            // If a match was found, break to process the next part of the pattern
            if (match_len > 0) {
                break;
            }

            // Otherwise, advance the string pointer and try again
            str++;
        }

        // If no match was found for this fragment, the overall match fails
        if (match_len <= 0) {
            return 0;
        }
    }

    // If the pattern is fully consumed, ensure the string is also fully consumed
    return str == str_end;
}