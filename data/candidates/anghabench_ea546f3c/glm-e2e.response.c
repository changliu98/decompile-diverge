void insert_dle(char *dst, char **src, int len) {
    while (len > 0) {
        len--;
        *dst = **src;
        dst++;
        (*src)++;
        
        // If the copied byte is the DLE character, insert another DLE to escape it
        if (*((*src) - 1) == DLE) {
            *dst = DLE;
            dst++;
        }
    }
}