int fatfs_get_sfn_display_name(char *out, const char *in)
{
    int len = 0;
    char c;

    while (*in && len < 12) {
        c = *in++;
        if (c == ' ')
            continue;
        if (c >= 'A' && c <= 'Z')
            c += 0x20;
        *out++ = c;
        len++;
    }
    *out = 0;

    return 1;
}