int __cdecl toml_value_string(toml_unparsed_t src, char **ret, int *len)
{
    char *parsed_str;
    bool multiline = false;
    const char *start_ptr;
    const char *end_ptr;

    *ret = NULL;
    if (!src)
        return -1;

    char qchar = src[0];
    int srclen = strlen(src);

    // Must be quoted with single (') or double (") quotes
    if (qchar != '\'' && qchar != '"')
        return -1;

    if (qchar == src[1] && qchar == src[2])
    {
        // Multi-line string (e.g., '''...''' or """...""")
        multiline = true;
        start_ptr = src + 3;
        end_ptr = &src[srclen - 3];

        // Validate closing quotes and bounds
        if (start_ptr > end_ptr || *end_ptr != qchar || end_ptr[1] != qchar || end_ptr[2] != qchar)
            return -1;

        // Skip immediate newline right after opening quotes
        if (*start_ptr == '\n')
        {
            start_ptr = src + 4;
        }
        else if (*start_ptr == '\r' && src[4] == '\n')
        {
            start_ptr = src + 5;
        }
    }
    else
    {
        // Single-line string (e.g., '...' or "...")
        start_ptr = src + 1;
        end_ptr = &src[srclen - 1];

        // Validate closing quote and bounds
        if (start_ptr > end_ptr || *end_ptr != qchar)
            return -1;
    }

    int content_len = (int)(end_ptr - start_ptr);

    // Parse string based on quote type (single quotes are literal, double allow escapes)
    if (qchar == '\'')
        parsed_str = norm_lit_str(start_ptr, content_len, len, multiline, NULL, 0);
    else
        parsed_str = norm_basic_str(start_ptr, content_len, len, multiline, NULL, 0);

    *ret = parsed_str;
    if (*ret)
        return 0;

    return -1;
}