bool wc_unescape(char *output, const char *wildcard)
{
    while (*wildcard) {
        if (*wildcard == '\\') {
            wildcard++;
            /* We are lenient about trailing backslashes in non-wildcards. */
            if (*wildcard) {
                if (output)
                    *output++ = *wildcard;
                wildcard++;
            }
        } else if (*wildcard == '*' || *wildcard == '?' ||
                   *wildcard == '[' || *wildcard == ']') {
            return false;              /* it's a wildcard! */
        } else {
            if (output)
                *output++ = *wildcard;
            wildcard++;
        }
    }
    if (output)
        *output = '\0';
    return true;                       /* it's clean */
}