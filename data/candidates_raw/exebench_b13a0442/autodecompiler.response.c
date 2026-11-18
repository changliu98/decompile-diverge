void reverse(char s[])
{
    char c;
    int i, j;

    for (j = 0; ; ++j) {
        if (s[j] == '\0') {
            --j;
            break;
        }
    }

    for (i = 0; i < j; ++i) {
        c = s[j];
        s[j] = s[i];
        s[i] = c;
        --j;
    }
}