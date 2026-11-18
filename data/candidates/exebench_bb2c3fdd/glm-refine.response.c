void __cdecl reverse(char *s)
{
    // Calculate the length of the string by iterating until the null terminator
    size_t length = 0;
    for (char *p = s; *p != '\0'; ++p)
        ++length;

    // Swap characters from the outside in
    for (size_t i = 0; i < length / 2; ++i)
    {
        char c = s[i];
        s[i] = s[length - i - 1];
        s[length - i - 1] = c;
    }
}