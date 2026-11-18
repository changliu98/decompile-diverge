void ReplaceXmpValue(char *str, size_t start, size_t end, char *replace) {
    size_t len = strlen(str);
    size_t replace_len = strlen(replace);
    size_t new_len = len - (end - start) + replace_len;
    if (new_len > len) {
        char *tmp = (char *)realloc(str, new_len);
        memmove(tmp + start + replace_len, tmp + end, len - end);
        memcpy(tmp + start, replace, replace_len);
        if (new_len > len) {
            tmp[new_len] = '\0';
        }
    }
}