void squeeze(char s1[], char s2[])
{
    int i, j;
    char c, d;
    char *ptr1, *ptr2;

    ptr1 = s1;
    ptr2 = s2;

    while (*s1 != '\0') {
        c = 0;
        do {
            c = (*s1 == *ptr2) ? 1 : 0;
            ptr2++;
        } while ((d = (*ptr2 == '\0')) == 0 && !c);
        if (!c) {
            *ptr1 = *s1;
            ptr1++;
        }
        s1++;
    }

    *ptr1 = '\0';
}