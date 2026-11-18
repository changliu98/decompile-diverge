char* object_desc_chr(char* str, char c) {
    str[0] = c;
    str[1] = '\0';
    return str + 1;
}