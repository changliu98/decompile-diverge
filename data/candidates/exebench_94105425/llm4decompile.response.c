void strrev(char *str)
{
    char *start = str;
    char *end = str;

    while (end && *end)
        end++;

    for (end--; start < end; start++, end--)
    {
        *start = *start ^ *end;
        *end = *start ^ *end;
        *start = *start ^ *end;
    }
}