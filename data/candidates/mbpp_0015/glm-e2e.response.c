char** func0(char* str, int* count) {
    char** result = NULL;
    *count = 0;
    int len = strlen(str);
    int i = 0;

    while (i < len) {
        if (isspace((unsigned char)str[i])) {
            i++;
        } else {
            int start = i;
            i++;
            while (i < len && !isspace((unsigned char)str[i])) {
                i++;
            }
            int end = i;
            int wordlen = end - start;
            char* word = (char*)malloc(wordlen + 1);
            strncpy(word, str + start, wordlen);
            word[wordlen] = '\0';
            result = (char**)realloc(result, (*count + 1) * sizeof(char*));
            result[*count] = word;
            (*count)++;
        }
    }

    return result;
}