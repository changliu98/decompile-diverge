int lemon_strcpy(char *s, char *t) {
    while ((*s++ = *t++)!= '\0')
        continue;
    return *(s - 1);
}