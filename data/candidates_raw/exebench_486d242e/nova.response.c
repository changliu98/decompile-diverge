void func0(char *s) {
    if (*s) {
        if (*s!= 'p' && *s!= '\\' && *s!= 'S')
            *s = *s ^ 15;
        func0(s + 1);
    }
}