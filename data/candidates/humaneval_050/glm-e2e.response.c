void func0(char *str, int flag) {
    int shift = 21;
    if (flag != 0) {
        shift = 5;
    }
    
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
        int shifted_val = ((str[i] - 'a') + shift) % 26 + 'a';
        str[i] = (char)shifted_val;
    }
}