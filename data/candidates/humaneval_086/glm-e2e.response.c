char *func0(const char *input_str) {
    int input_len = strlen(input_str);
    char *result_str = (char *)malloc(input_len + 2);
    
    int res_idx = 0;
    int word_len = 0;
    char word_buf[80];
    
    for (int i = 0; i <= input_len; i++) {
        if (input_str[i] == ' ' || input_str[i] == '\0') {
            // Sort the current word in descending order (Bubble Sort)
            for (int j = 0; j < word_len - 1; j++) {
                for (int k = j + 1; k < word_len; k++) {
                    if (word_buf[j] > word_buf[k]) {
                        char temp = word_buf[j];
                        word_buf[j] = word_buf[k];
                        word_buf[k] = temp;
                    }
                }
            }
            
            // Append a space before the word if it's not the first word
            if (res_idx > 0) {
                result_str[res_idx++] = ' ';
            }
            
            // Append the sorted word to the result string
            for (int j = 0; j < word_len; j++) {
                result_str[res_idx++] = word_buf[j];
            }
            
            word_len = 0;
        } else {
            // Add character to the current word buffer
            word_buf[word_len++] = input_str[i];
        }
    }
    
    // Null-terminate the result string
    result_str[res_idx] = '\0';
    
    return result_str;
}