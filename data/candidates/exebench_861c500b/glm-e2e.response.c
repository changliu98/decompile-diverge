char* fix(char* dst, const char* src) {
    int j = 0;
    int i = 0;
    
    while (src[i] != '\0') {
        if (src[i] == 8) { // 8 is the ASCII code for the backspace character ('\b')
            j--;
            if (j < 0) {
                j = 0;
            }
        } else {
            dst[j++] = src[i];
        }
        i++;
    }
    
    dst[j] = '\0';
    return dst;
}