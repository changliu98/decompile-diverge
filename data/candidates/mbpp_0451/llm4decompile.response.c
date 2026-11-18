char *func0(char *text1) {
    int i, j;
    for (i = 0, j = 0; text1[i] != '\0'; i++) {
        if (!((*__ctype_b_loc ())[(int) ((unsigned char) text1[i])] & 0x2000)) {
            text1[j++] = text1[i];
        }
    }
    text1[j] = '\0';
    return text1;
}