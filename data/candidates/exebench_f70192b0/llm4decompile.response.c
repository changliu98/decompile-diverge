int i_to_str(int val, char *str)
{
    char *begin = str;
    char *end;
    int i, len;
    char temp;

    if (val < 0)
    {
        *str = '-';
        str++;
        val = -val;
    }

    end = str;
    do
    {
        *end = (val % 10) + '0';
        end++;
        val /= 10;
    } while (val != 0);

    *end = '\0';
    len = end - begin;
    for (i = 0; i < len / 2; i++)
    {
        temp = begin[i];
        begin[i] = begin[len - 1 - i];
        begin[len - 1 - i] = temp;
    }

    return end - str;
}