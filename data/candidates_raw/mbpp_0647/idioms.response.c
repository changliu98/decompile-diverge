char **str_split(char *str, int *count)
{
    int len = strlen(str);
    char **words = (char **)malloc(len * sizeof(char *));
    if (words == ((void *)0)) {
        perror("Failed to allocate memory");
        exit(1);
    }
    int word_count = 0;
    int start = 0;
    int i;
    for (i = 1; i <= len; i++) {
        if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISupper) || str[i] == '\0') {
            int word_len = i - start;
            words[word_count] = (char *)malloc((i - start + 1) * sizeof(char));
            if (words[word_count] == ((void *)0)) {
                perror("Failed to allocate memory");
                exit(1);
            }
            memcpy(words[word_count], &str[start], word_len);
            words[word_count][word_len] = '\0';
            start = i;
            word_count++;
        }
    }
    *count = word_count;
    return words;
}