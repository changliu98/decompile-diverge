void __cdecl reverse(char *s)
{
    size_t i = 0;
    
    // Find the length of the string, stopping if a newline ('\n') is encountered.
    // The original condition `s[i] != 10` checks for the newline character.
    while (s[i] != '\0' && s[i] != '\n') {
        i++;
    }

    // Reverse the string in-place up to the found length.
    // The original loop condition `ia < j` correctly handles both even and odd lengths.
    for (size_t ia = 0, j = i - 1; ia < j; ia++, j--) {
        char tmp = s[ia];
        s[ia] = s[j];
        s[j] = tmp;
    }
}