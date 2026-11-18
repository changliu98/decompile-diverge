void func0(char *s) {
    int i = 0;
    while (1) {
        if (s[i] == '\0')
            break;
        if (s[i] =='')
            s[i] = '_';
        i++;
    }
}