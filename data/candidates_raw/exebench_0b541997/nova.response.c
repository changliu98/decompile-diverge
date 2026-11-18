int func0(char *s, char *t) {
    while ((*s++ = *t++)!= '\0')
        continue;
    return *(s - 1);
}