void __cdecl reverse(char *s)
{
    char *start = s;
    char *end = s;

    // Find the null terminator to determine the end of the string
    while (*end)
        ++end;

    // Step back one character to point to the last valid character
    --end;

    // Swap characters from the outside in
    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        
        ++start;
        --end;
    }
}