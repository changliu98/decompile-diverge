char *func0(char *s) {
    static char func0ed[11890];
    int i;
    strcpy(func0ed, s);
    for (i = 0; func0able[i]; i++) {
        if (isupper(func0able[i]))
            func0ed[i] = tolower(func0ed[i]);
        else if (islower(func0able[i]))
            func0ed[i] = toupper(func0ed[i]);
    }
    return func0ed;
}