void __cdecl reverse(char *str)
{
    if (str == NULL || *str == '\0')
        return;

    char *left = str;
    char *right = str + strlen(str) - 1;

    while (left < right)
    {
        char temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}