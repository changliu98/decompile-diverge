void __cdecl rev(char *str) {
    int i;
    char temp;
    int len;

    // Calculate the length of the string
    for (len = 0; str[len]; ++len)
        ;

    // Swap characters from the outside in
    for (i = 0; i < len / 2; ++i) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}