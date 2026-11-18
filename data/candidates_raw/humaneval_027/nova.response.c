void func0(char *str, char *str2) {
    int i;
    int len = strlen(str);

    i = 0;
    while (i < len) {
        char c = str[i];
        if (c >= 'a' && c <= 'z')
            c -= 32;
        else if (c >= 'A' && c <= 'Z')
            c += 32;
        str2[i] = c;
        i++;
    }
    str2[len] = '\0';
}