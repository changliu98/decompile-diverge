static void ck_decrypt(char *s) {
    if (*s) {
        if (*s!= 'p' && *s!= '\\' && *s!= 'S')
            *s ^= 0x0F;
        ck_decrypt(s + 1);
    }
}