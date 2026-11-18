void __cdecl reverse(char *s)
{
    char *left = s;
    char *right;

    // Find the null terminator to determine the end of the string
    for (right = s; *right; ++right)
        ;

    // Step back one character to the last valid character before the null terminator
    --right;

    // Swap characters from the outside in until the pointers meet
    while (left < right)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;

        ++left;
        --right;
    }
}