void toup(char *c) {
    char temp ='';
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;
}