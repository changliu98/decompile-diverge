int wc_match_inner(const char *wildcard, const char *target, size_t target_len)
{
    const char *target_end = target + target_len;
    const char *save_w, *save_t;
    int ret;


    if (*wildcard != '*') {
        ret = wc_match_fragment(&wildcard, &target, target_end);
        if (ret <= 0)
            return ret;
    }

    while (*wildcard) {
        do { if (!(*wildcard == '*')) __assert_fail("*wildcard == '*'", "func.c", 228, "int wc_match_inner(const char *, const char *, size_t)"); } while (0);

        while (*wildcard == '*')
            wildcard++;

        if (!*wildcard)
            return 1;

        save_w = wildcard;
        save_t = target;
        ret = 0;


        while (*target) {
            ret = wc_match_fragment(&wildcard, &target, target_end);
            if (ret < 0)
                return ret;





            if (ret > 0 && !*wildcard && target != target_end) {
                size_t len = target - save_t;
                target = target_end - len;
                wildcard = save_w;
                ret = wc_match_fragment(&wildcard, &target, target_end);
                return ret;
            }

            if (ret > 0)
                break;

            target++;
        }

        if (ret <= 0)
            return 0;
    }

    return target == target_end;
}