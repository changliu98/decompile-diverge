char * func0(char * text)
{
    size_t length = strlen(text);
    char * result = malloc(length * 2);
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if (i > 0 && (((*__ctype_b_loc ())[(int) ((text[i]))] & (0x0100)) != 0) && (((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (0x0200)) != 0 || ((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (0x0800)) != 0))
        {
            result[j++] = '_';
            result[j++] = tolower(text[i]);
        }
        else if (i > 0 && (((*__ctype_b_loc ())[(int) ((text[i]))] & (0x0100)) != 0) && (((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (0x0100)) != 0) && (((*__ctype_b_loc ())[(int) ((text[i + 1]))] & (0x0200)) != 0))
        {
            result[j++] = '_';
            result[j++] = tolower(text[i]);
        }
        else
        {
            result[j++] = tolower(text[i]);
        }
    }
    result[j] = 0;
    return result;
}