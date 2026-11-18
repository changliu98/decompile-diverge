static int wc_match_inner(
    const char *wildcard, const char *target, size_t target_len)
{
    const char *target_end = target + target_len;
    int ret;

    /*
     * Every time we see a '*' _followed_ by a fragment, we just
     * search along the string for a location at which the fragment
     * matches. The only special case is when we see a fragment
     * right at the start, in which case we just call the matching
     * routine once and give up if it fails.
     */
    if (*wildcard != '*') {
        ret = wc_match_fragment(&wildcard, &target, target_end);
        if (ret <= 0)
            return ret;                /* pass back failure or error alike */
    }

    while (*wildcard) {
        assert(*wildcard == '*');
        while (*wildcard == '*')
            wildcard++;

        /*
         * It's possible we've just hit the end of the wildcard
         * after seeing a *, in which case there's no need to
         * bother searching any more because we've won.
         */
        if (!*wildcard)
            return 1;

        /*
         * Now `wildcard' points at the next fragment. So we
         * attempt to match it against `target', and if that fails
         * we increment `target' and try again, and so on. When we
         * find we're about to try matching against the empty
         * string, we give up and return 0.
         */
        ret = 0;
        while (*target) {
            const char *save_w = wildcard, *save_t = target;

            ret = wc_match_fragment(&wildcard, &target, target_end);

            if (ret < 0)
                return ret;            /* syntax error */

            if (ret > 0 && !*wildcard && target != target_end) {
                /*
                 * Final special case - literally.
                 *
                 * This situation arises when we are matching a
                 * _terminal_ fragment of the wildcard (that is,
                 * there is nothing after it, e.g. "*a"), and it
                 * has matched _too early_. For example, matching
                 * "*a" against "parka" will match the "a" fragment
                 * against the _first_ a, and then (if it weren't
                 * for this special case) matching would fail
                 * because we're at the end of the wildcard but not
                 * at the end of the target string.
                 *
                 * In this case what we must do is measure the
                 * length of the fragment in the target (which is
                 * why we saved `target'), jump straight to that
                 * distance from the end of the string using
                 * strlen, and match the same fragment again there
                 * (which is why we saved `wildcard'). Then we
                 * return whatever that operation returns.
                 */
                target = target_end - (target - save_t);
                wildcard = save_w;
                return wc_match_fragment(&wildcard, &target, target_end);
            }

            if (ret > 0)
                break;
            target++;
        }
        if (ret > 0)
            continue;
        return 0;
    }

    /*
     * If we reach here, it must be because we successfully matched
     * a fragment and then found ourselves right at the end of the
     * wildcard. Hence, we return 1 if and only if we are also
     * right at the end of the target.
     */
    return target == target_end;
}