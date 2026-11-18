int __cdecl func0(const char *s)
{
    int result = 0;
    int n = strlen(s);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j <= n - i; ++j)
        {
            // 'j' represents the length of the substring.
            // 'i' is the starting index.
            // 'j + i - 1' is the ending index of the substring.
            if (check_Equality(s, i, j + i - 1))
                ++result;
        }
    }
    return result;
}