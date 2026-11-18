char* func0(const char* src, char old_char, char new_char) {
    static char str2[...]; // A static buffer located at 0x40a0
    int i = 0;
    
    strcpy(str2, src);
    
    while (i < strlen(str2)) {
        if (str2[i] == old_char) {
            str2[i] = new_char;
        }
        i++;
    }
    
    return str2;
}