void func0(char *str, int flag) {
    int len = strlen(str);
    int chunks = (len + 2) / 3;
    
    for (int i = 0; i < chunks; i++) {
        int chunk_size;
        if (i * 3 + 3 > len) {
            chunk_size = len - i * 3;
        } else {
            chunk_size = 3;
        }
        
        int n = chunk_size;
        char temp[4];
        
        strncpy(temp, str + i * 3, n);
        temp[n] = '\0';
        
        if (n == 3) {
            if (flag != 0) {
                // Rotate left
                char t = temp[2];
                temp[2] = temp[1];
                temp[1] = temp[0];
                temp[0] = t;
            } else {
                // Rotate right
                char t = temp[0];
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = t;
            }
        }
        
        strncpy(str + i * 3, temp, n);
    }
}