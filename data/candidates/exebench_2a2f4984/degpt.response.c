int cpy(char *dest, char *src)
{
    int index;
    // Copy characters from source string b to destination string a,
    // up to a maximum of 100 characters or until the null terminator is reached.
    for (index = 0; src[index] != '\0' && index < 100; index++) {
        dest[index] = src[index];
    }
    // Null-terminate the destination string.
    dest[index] = '\0';
    return 0;
}