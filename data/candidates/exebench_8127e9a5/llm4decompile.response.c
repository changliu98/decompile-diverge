void reverse(char str[])
{
    size_t str_len = 0;
    while (str[str_len])
        str_len++;

    if (str_len > 0)
    {
        size_t i = 0;
        size_t j = str_len - 1;
        while (i < j)
        {
            char tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
            i++;
            j--;
        }
    }
}