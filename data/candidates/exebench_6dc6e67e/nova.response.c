void copia(char *s, char *t) {
    while ((*s++ = *t++)!= '\0')
        ;
    *s = '\0';
}