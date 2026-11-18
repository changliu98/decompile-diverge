char *func0(char *s, char c) {
    bool found = false;
    while (!found) {
        if (*s == c)
            found = true;
        if (!found && *s == '\0')
            break;
        if (!found)
            s++;
    }
    if (*s!= '\0')
        *s++ = '\0';
    return s;
}