char *m_stpcpy(char *s, char *t) {
    size_t i = 0;
    while (1) {
        if (t[i]) {
            s[i] = t[i];
            i++;
        } else {
            s[i] = '\0';
            break;
        }
    }
    return s + i;
}