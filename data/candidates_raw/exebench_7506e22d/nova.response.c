void func0(char *c) {
    char temp ='';
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;
}