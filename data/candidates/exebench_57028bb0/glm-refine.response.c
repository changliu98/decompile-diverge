char *__cdecl ft_strcpy(char *dest, char *src)
{
    // Calculate the length of dest
    size_t dest_len = 0;
    while (dest[dest_len++]);

    // Calculate the length of src
    size_t src_len = 0;
    while (src[src_len++]);

    // Non-standard behavior: return an empty string if src is longer than dest
    if (src_len > dest_len)
        return (char *)"";

    // Copy src to dest
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}