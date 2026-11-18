char **func0(char *str, int *size) {
    char **ret = NULL;
    *size = 0;
    int len = strlen(str);
    int i = 0;
    while (i < len) {
        if (isalpha(str[i])) {
            int start = i;
            bool is_word = true;
            while (i < len) {
                if (isalpha(str[i])) {
                    i++;
                } else {
                    is_word = false;
                    break;
                }
            }
            if (is_word) {
                int word_len = i - start;
                char *word = (char *)malloc(sizeof(char) * (word_len + 1));
                strncpy(word, str + start, word_len);
                word[word_len] = '\0';
                ret = (char **)realloc(ret, (*size + 1) * sizeof(char *));
                ret[*size] = word;
                (*size)++;
            }
        }
        i++;
    }
    return ret;
}