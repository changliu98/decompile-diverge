int func0(const char *str) {
    int new_sentence = 1;
    int in_word = 0;
    int count = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            if (in_word) {
                in_word = 0;
                count++;
            }
        } else if (str[i] == 'I') {
            if (new_sentence) {
                in_word = 1;
            }
        } else if (!isspace(str[i])) {
            in_word = 0;
        }
        
        if (!isspace(str[i])) {
            new_sentence = 0;
        }
        
        if (str[i] == '.' || str[i] == '?' || str[i] == '!') {
            new_sentence = 1;
        }
    }
    
    return count;
}