void string_reverse(char* s)
{
    char* start = s;
    char* end = s;
    char tmp;

    while(*end)
        end++;

    while(start < end)
    {
        tmp = *start;
        *start = *(end-1);
        *(end-1) = tmp;
        start++;
        end--;
    }
}