static void func0(char *s) {
    if (*s) {
        if (*s!= 'p' && *s!= '\\' && *s!= 'S')
            *s ^= 0x0F;
        func0(s + 1);
    }
}