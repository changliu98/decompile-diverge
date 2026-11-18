void reverse(char *str) {
    char *p1 = str;
    char *p2 = str;
    char temp;

    // Find the end of the string
    while (*p2 != '\0') {
        p2++;
    }
    p2--; // Move back one step to the last character before the null terminator

    // Swap characters from the outside in
    while (p1 < p2) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;

        p1++;
        p2--;
    }
}