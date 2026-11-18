int func0(char *txt)
{
    int len = strlen(txt);
    if (len == 0)
        return 0;
    char last_char = txt[len - 1];
    if (!((*__ctype_b_loc ())[(int) ((last_char))] & (unsigned short) _ISalpha))
        return 0;
    if (len == 1)
        return 1;
    char second_last_char = txt[len - 2];
    if (((*__ctype_b_loc ())[(int) ((second_last_char))] & (unsigned short) _ISalpha))
        return 0;
    return 1;
}