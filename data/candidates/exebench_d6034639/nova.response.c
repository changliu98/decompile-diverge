int fatfs_get_sfn_display_name(char *dest, char *src) {
    int i = 0;
    char c;
    while (1) {
        if (src[0] == '\0' || i >= 12) {
            break;
        }
        c = *src++;
        if (c =='') {
            continue;
        }
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
        *dest++ = c;
        i++;
    }
    *dest = '\0';
    return 1;
}