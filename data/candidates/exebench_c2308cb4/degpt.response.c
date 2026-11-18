char *ft_strcpy(char *destination, char *source)
{
    int index;

    // Copy characters from src to dst until the null terminator is reached
    for (index = 0; source[index] != '\0'; index++)
        destination[index] = source[index];
    // Copy the null terminator to the end of dst
    destination[index] = '\0';
    // Return the destination string pointer
    return (destination);
}