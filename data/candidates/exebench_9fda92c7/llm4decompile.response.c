void reverse(char s[])
{
    char *start = s;
    char *end = s;
    char tmp;

    while(*end++)
        ;
    end -= 2;

    while(start < end)
    {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}