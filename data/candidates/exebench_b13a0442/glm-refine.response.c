void __cdecl strrev(char *s)
{
    if (!s)
        return;

    // Calculate the length of the string
    size_t len = 0;
    while (s[len])
        ++len;

    // Reverse the string in-place
    for (size_t i = 0, j = len - 1; i < j; ++i, --j)
    {
        char c = s[j];
        s[j] = s[i];
        s[i] = c;
    }
}