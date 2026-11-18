void __cdecl func0(const char *input, char *output)
{
    int i;

    // Iterate through the string until the null terminator is encountered
    for (i = 0; input[i]; ++i)
    {
        // Cast to unsigned char to prevent sign-extension issues with `tolower`
        output[i] = tolower((unsigned char)input[i]);
    }
    
    // Ensure the destination string is null-terminated
    output[i] = '\0';
}