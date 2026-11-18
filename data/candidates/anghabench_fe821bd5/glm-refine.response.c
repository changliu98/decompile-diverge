bool ok_cp1251(const char *s, int n)
{
    for (int i = 1; i < n; ++i)
    {
        // -104 as an unsigned byte is 0x98 (152), 
        // which represents the non-breaking space in Windows-1251.
        if ((unsigned char)s[i] == 0x98)
            return false;
    }
    return true;
}