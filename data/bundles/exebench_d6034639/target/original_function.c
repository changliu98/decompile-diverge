int fatfs_get_sfn_display_name(char* out, char* in)
{
    int len = 0;
    while (*in && len <= 11)
    {
        char a = *in++;

        if (a == ' ')
            continue;

        else if ((a>='A') && (a<='Z'))
            a+= 32;

        *out++ = a;
        len++;
    }

    *out = '\0';
    return 1;
}