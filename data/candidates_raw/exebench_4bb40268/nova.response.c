void func0(char *s, char *t, char *o) {
    *o = *(s - 1);
    if (t - s == 4)
        *o = 'f';
}