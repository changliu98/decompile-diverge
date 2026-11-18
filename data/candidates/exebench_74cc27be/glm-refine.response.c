char *Q_bstrcpy(char *dest, const char *src)
{
    char *start = dest;

    // Copy characters from src to dest until the null terminator is encountered
    while (*src)
    {
        *dest++ = *src++;
    }

    // Append the null terminator
    *dest = '\0';

    return start;
}