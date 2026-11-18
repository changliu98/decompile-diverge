void unhide(char *str) {
    int key_idx = 0;
    int i = 0;

    while (str[i] != '\0') {
        str[i] = str[i] - keys[key_idx];
        
        key_idx++;
        if (key_idx == 3) {
            key_idx = 0;
        }
        
        i++;
    }
}