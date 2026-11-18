void ck_encrypt(char *s) {
    if (*s) {
        if (*s!= 'p' && *s!= '\\' && *s!= 'S')
            *s = *s ^ 15;
        ck_encrypt(s + 1);
    }
}