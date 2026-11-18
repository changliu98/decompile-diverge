char* func0(int n, char** sentences) {
    int num_words = 0;
    for (int i = 0; i < n; i++) {
        char* p = sentences[i];
        char buf[100];
        int buf_len = 0;
        
        while (*p != '\0') {
            if (isspace(*p)) {
                if (buf_len > 0) {
                    buf[buf_len] = '\0';
                    int found = 0;
                    for (int j = 0; j < num_words; j++) {
                        if (strcmp(words[j].word, buf) == 0) {
                            words[j].count++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        strcpy(words[num_words].word, buf);
                        words[num_words].count = 1;
                        num_words++;
                    }
                    buf_len = 0;
                }
            } else {
                buf[buf_len++] = *p;
            }
            p++;
        }
        
        if (buf_len > 0) {
            buf[buf_len] = '\0';
            int found = 0;
            for (int j = 0; j < num_words; j++) {
                if (strcmp(words[j].word, buf) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(words[num_words].word, buf);
                words[num_words].count = 1;
                num_words++;
            }
        }
    }
    
    int max_count = 0;
    int max_index = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
            max_index = i;
        }
    }
    
    return words[max_index].word;
}