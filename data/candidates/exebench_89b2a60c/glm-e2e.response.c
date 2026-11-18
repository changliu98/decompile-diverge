char *char_replace(char *str, char old_char, char new_char) {
    char *ret;
    char *ptr;

    if (str == NULL || *str == '\0') {
        ret = str;
    } else {
        while ((ptr = strchr(str, old_char)) != NULL) {
            *ptr = new_char;
            ptr++;
        }
        ret = str;
    }
    
    return ret;
}