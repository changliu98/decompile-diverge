
void
ck_encrypt(char * s) {
    while (*s) {
        if (*s != 'p' && *s != '\\' && *s != 'S')
          *s ^= 0x0F;
        s++;
    }
}
