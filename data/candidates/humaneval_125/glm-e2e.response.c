char **func0(const char *str, int *count) {
    int word_len = 0;
    int vowel_count = 0;
    int word_count = 0;
    int len = strlen(str);
    char **result = NULL;
    char buffer[101]; // 0x65 = 101 bytes

    memset(buffer, 0, 101);

    // Check if the string contains a space or a comma
    if (strchr(str, ' ') != NULL || strchr(str, ',') != NULL) {
        result = (char **)malloc((len + 1) * sizeof(char *));
        
        for (int i = 0; i <= len; i++) {
            char c = str[i];
            if (c == ' ' || c == ',' || c == '\0') {
                if (word_len > 0) {
                    buffer[word_len] = '\0';
                    result[word_count] = strdup(buffer);
                    word_count++;
                    word_len = 0;
                }
            } else {
                buffer[word_len++] = c;
            }
        }
    } else {
        // Count vowels with a specific condition
        for (int i = 0; i < len; i++) {
            if (isalpha(str[i])) {
                if ((str[i] - 'a') % 2 == 1) {
                    vowel_count++;
                }
            }
        }
        
        result = (char **)malloc(sizeof(char *));
        result[0] = (char *)malloc(12); // 0xC = 12 bytes
        sprintf(result[0], "%d", vowel_count);
        word_count = 1;
    }

    *count = word_count;
    return result;
}