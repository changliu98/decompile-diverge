void __cdecl Reverse(char *s)
{
    // Find the length of the string (equivalent to strlen(s))
    int len = 0;
    while (s[len]) {
        ++len;
    }

    // Point to the last valid character (ignoring the null terminator)
    int right = len - 1;

    // If the string ends with a newline character ('\n' == 10), exclude it from the reversal
    if (s[right] == '\n') {
        --right;
    }

    // Swap characters from the outside in
    int left = 0;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        ++left;
        --right;
    }
}