int affs_intl_toupper(int ch)
{
    if ((ch >= 'a' && ch <= 'z') ||
 (ch >= 224 && ch <= 254 && ch != 247))
 ch -= 'a' - 'A';
    return ch;
}