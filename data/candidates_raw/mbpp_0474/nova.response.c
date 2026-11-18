char *func0(char *s, char old, char new) {
    static char digits[] = "0123456789";
    static char *p = digits;
    static char buf[10];
    int i;

    strcpy(buf, s);
    for (i = 0; i < strlen(digits); i++)
        buf[i] = digits[i] == old? new : buf[i];
    return buf;
}