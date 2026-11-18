char *ft_strcpy(char *dest, char *src) {
    int i = -1;
    while (1) {
        i++;
        if (src[i] == '\0') {
            dest[i] = '\0';
            break;
        }
        dest[i] = src[i];
    }
    return dest;
}