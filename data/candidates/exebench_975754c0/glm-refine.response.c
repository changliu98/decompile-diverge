void __cdecl reverse(char *s)
{
    int len = 0;
    
    // Calculate the length of the string
    while (s[len]) {
        len++;
    }

    // Reverse the string in-place
    for (int i = 0; i < len / 2; ++i) {
        char c = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = c;
    }
}