void pattern_check_unclosed_captures(struct Pattern *pat) {
    for (int i = 1; i < pat->unknown2; i++) {
        if (pat->captures[i] == -1) {
            int depth = 0;
            const char *curr = pat->p;
            const char *end = pat->p + strlen(pat->p);
            
            while (curr < end) {
                if (*curr == '%') {
                    curr += 2;
                } else if (*curr == '(') {
                    depth++;
                    if (depth == i) {
                        break;
                    }
                    curr++;
                } else {
                    curr++;
                }
            }
            
            pattern_set_error(pat, 3, curr - pat->p);
            return;
        }
    }
}