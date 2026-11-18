char *__cdecl func0(const char *src, const char *replacement_char)
{
    int i;
    int j = 0;

    // Iterate through the source string until the null terminator is reached
    for (i = 0; src[i] != '\0'; ++i)
    {
        // Replace space characters (' ') with the provided replacement character
        char c = (src[i] == ' ') ? *replacement_char : src[i];
        
        func0_str2[j++] = c;
    }
    
    // Null-terminate the destination string
    func0_str2[j] = '\0';
    
    return func0_str2;
}