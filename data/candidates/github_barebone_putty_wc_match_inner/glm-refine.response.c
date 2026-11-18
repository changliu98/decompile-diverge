int __cdecl wc_match_inner(const char *wildcard, const char *target, size_t target_len)
{
    const char *saved_t;
    const char *saved_w;
    int ret;
    const char *target_end = target + target_len;
    const char *w = wildcard;
    const char *t = target;

    // If the pattern doesn't start with '*', match the initial fragment exactly
    if (*wildcard != '*')
    {
        ret = wc_match_fragment(&w, &t, target_end);
        if (ret <= 0)
            return ret;
    }

    // Process the rest of the wildcard pattern
    while (*w != '\0')
    {
        assert(*w == '*');

        // Skip consecutive '*' characters
        while (*w == '*')
            ++w;

        // If the pattern ends with '*', it matches the rest of the target
        if (*w == '\0')
            return 1;

        // Try to match the next fragment starting from the current target position
        ret = 0;
        for (; *t != '\0'; ++t)
        {
            saved_w = w;
            saved_t = t;
            
            ret = wc_match_fragment(&w, &t, target_end);
            if (ret < 0)
                return ret;

            // If the fragment matches and it's the end of the wildcard, 
            // but there's still target left, backtrack to the end and do a final match.
            if (ret > 0 && *w == '\0' && t != target_end)
            {
                t = target_end + (saved_t - t);
                w = saved_w;
                return wc_match_fragment(&w, &t, target_end);
            }

            // If the fragment matched, break and proceed to the next wildcard segment
            if (ret > 0)
                break;
        }

        // If the fragment failed to match anywhere in the remaining target
        if (ret <= 0)
            return 0;
    }

    // Return 1 if we reached the exact end of the target, 0 otherwise
    return t == target_end;
}