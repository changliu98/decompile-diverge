void func0(char *s, char *t) {
    int i, j;
    char c;
    char *lowercase = "abcdefghijklmnopqrstuvwxyz";
    for (i = 0; (c = s[i])!= '\0'; i++) {
        c = s[i];
        if (isupper(c))
            c = tolower(c);
        else if (islower(c))
            c = toupper(c);
        for (j = 0; lowercase[j]!= '\0'; j++) {
            if (c == lowercase[j] && j < 11)
                c += 2;
            else
                break;
        }
        t[i] = c;
    }
    t[i] = '\0';
}