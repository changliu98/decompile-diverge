char *build_ustar_entry_name(char *dest, char *src, long src_length, char *insert)
{
    char *prefix_end;
    char *filename;
    char *filename_end;
    char *suffix_end;
    int need_slash = 0;
    long insert_length = 0;
    long suffix_length = 99;
    if (insert)
        insert_length = str_strlen(insert)+2;
    if (src_length < 100 && !insert)
    {
        str_strlcpy(dest, src, src_length);
        dest[src_length] = '\0';
        return dest;
    }
    for (filename_end = src + src_length; ; filename_end -= 2)
    {
        while (filename_end > src && *(filename_end - 1) == '/')
            filename_end--;
        if (filename_end > src + 1 && *(filename_end - 1) == '.' &&
            *(filename_end - 2) == '/')
        {
            filename_end -= 2;
            need_slash = 1;
        }
        else
            break;
    }
    if (need_slash)
        suffix_length = 98;
    for (filename = filename_end - 1; ; filename--)
    {
        int is_not_slash = 0;
        if (filename > src)
            is_not_slash = *filename != '/';
        if (!is_not_slash)
            break;
    }
    if (*filename == '/' && filename < filename_end - 1)
        filename++;
    suffix_length -= insert_length;
    if (filename + suffix_length < filename_end)
        filename_end = filename + suffix_length;
    suffix_length -= (filename_end - filename);
    prefix_end = src + 155;
    if (prefix_end > filename)
        prefix_end = filename;
    while (1)
    {
        int is_not_slash = 0;
        if (prefix_end > src)
            is_not_slash = *prefix_end != '/';
        if (!is_not_slash)
            break;
        prefix_end--;
    }
    if (prefix_end < filename && *prefix_end == '/')
        prefix_end++;
    suffix_end = prefix_end + suffix_length;
    if (suffix_end > filename)
        suffix_end = filename;
    while (1)
    {
        int is_not_slash = 0;
        if (suffix_end > prefix_end)
            is_not_slash = *suffix_end != '/';
        if (!is_not_slash)
            break;
        suffix_end--;
    }
    if (suffix_end < filename && *suffix_end == '/')
        suffix_end++;
    char *dest_end = dest;
    if (prefix_end > src)
    {
        str_strlcpy(dest, src, prefix_end - src);
        dest_end = dest + (prefix_end - src);
    }
    if (suffix_end > prefix_end)
    {
        str_strlcpy(dest_end, prefix_end, suffix_end - prefix_end);
        dest_end += (suffix_end - prefix_end);
    }
    if (insert)
    {
        str_strlcpy(dest_end, insert, insert_length);
        dest_end += str_strlen(insert);
        *dest_end++ = '/';
    }
    str_strlcpy(dest_end, filename, filename_end - filename);
    dest_end += (filename_end - filename);
    if (need_slash)
        *dest_end++ = '/';
    *dest_end = '\0';
    return dest;
}