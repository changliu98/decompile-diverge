long func0(char *word, char *list[], char *text, long text_size) {
    long word_len = strlen(word);
    long i = -1;
    long found = FALSE;
    long index = 0;

    for (i = 0; i < MAX_WORDS; i++) {
        if (list[i]!= NULL) {
            if (strncmp(list[i], word, word_len) == 0) {
                if (strlen(list[i]) == word_len) {
                    index = i;
                    break;
                } else if (i == -1) {
                    i = index;
                } else if (text!= NULL) {
                    if (memcmp(text + i * text_size, text + index * text_size,
                               text_size)!= 0) {
                        found = TRUE;
                    }
                }
            }
        }
    }

    if (found) {
        index = -2;
    } else {
        index = index;
    }

    return index;
}