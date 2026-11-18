int __cdecl count_vowels(const char *str, const char *vowels)
{
    int count = 0;

    while (*str)
    {
        for (const char *v = vowels; *v; ++v)
        {
            if (*str == *v)
            {
                ++count;
                break;
            }
        }
        ++str;
    }

    return count;
}