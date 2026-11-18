static void pattern_check_unclosed_captures(Pattern_State* ps) {
    for(int i = 1; i < ps->capture_count; i++) {
        if(ps->captures[i].size == PATTERN_CAPTURE_UNFINISHED) {
            // Find position of unclosed capture
            int captures = 0;
            const char* pat = ps->pattern_base;
            while(pat < ps->pattern_base + strlen(ps->pattern_base)) {
                if(*pat == PATTERN_ESCAPE) {
                    pat += 2;
                    continue;
                }
                if(*pat == '(') {
                    if(++captures == i) break;
                }
                pat++;
            }
            pattern_set_error(ps, PATTERN_ERR_UNCLOSED_CAPTURE, pat - ps->pattern_base);
            return;
        }
    }
}