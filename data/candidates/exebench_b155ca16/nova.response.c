char *object_desc_chr(char *s, char c) {
    *s = c;
    *(s + 1) = '\0';
    return s;
}