void __cdecl int2str(int value, int i, char *output)
{
    while (i)
    {
        *output++ = (value / i % 10) + '0';
        i /= 10;
    }
    *output = '\0';
}