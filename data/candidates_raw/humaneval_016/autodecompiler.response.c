int count_unique(char *s)
{
    int seen[256];
    int count = 0;
    int i;

    memset(seen, 0, sizeof(int)*256);

    for (i = 0; ; i++) {
        char c;
        if (s[i] == '\0') break;
        c = tolower(s[i]);
        if (!seen[c] && (((*___ctype_b_loc ())[(c) & 0xff] & (unsigned short int) 1024) != 0)) {
            seen[c] = 1;
            count++;
        }
    }

    return count;
}