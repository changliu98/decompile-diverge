void pattern_check_unclosed_captures(struct pattern_state *ps)
{
    int i;
    for (i = 1; i < ps->capture_count; i++) {
        if (ps->captures[i].size == -1) {
            int captures = 0;
            char *c = ps->pattern_base;
            while (c < &ps->pattern_base[pattern_length(ps->pattern_base)]) {
                if (*c == '%') {
                    c += 2;
                }
                else if (*c == '(' && ++captures == i) {
                    break;
                }
                else {
                    c++;
                }
            }
            set_error(ps, PATTERN_ERR_UNCLOSED_CAPTURE, c - ps->pattern_base);
            return;
        }
    }
}