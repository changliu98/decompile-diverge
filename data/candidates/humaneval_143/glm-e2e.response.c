void func0(char *dest, char *src) {
    int dest_idx = 0;
    int word_len = 0;
    int i = 0;
    
    while (src[i] != '\0') {
        if (src[i] == ' ') {
            if (word_len > 1) {
                int is_prime = 1;
                for (int j = 2; j * j <= word_len; j++) {
                    if (word_len % j == 0) {
                        is_prime = 0;
                        break;
                    }
                }
                if (is_prime) {
                    if (dest_idx > 0) {
                        dest[dest_idx++] = ' ';
                    }
                    memcpy(dest + dest_idx, src + i - word_len, word_len);
                    dest_idx += word_len;
                }
            }
            word_len = 0;
        } else {
            word_len++;
        }
        i++;
    }
    
    // Check the last word
    if (word_len > 1) {
        int is_prime = 1;
        for (int j = 2; j * j <= word_len; j++) {
            if (word_len % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            if (dest_idx > 0) {
                dest[dest_idx++] = ' ';
            }
            memcpy(dest + dest_idx, src + i - word_len, word_len);
            dest_idx += word_len;
        }
    }
    
    dest[dest_idx] = '\0';
}