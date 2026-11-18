char** func0_word_len(int n, char* sentence, int* output_size) {
    int idx = 0;
    char* pch = strtok(sentence, " ");
    while (1) {
        if (pch == NULL) break;
        if (strlen(pch) > n) {
            func0_word_len[idx++] = pch;
        }
        pch = strtok(NULL, " ");
    }
    *output_size = idx;
    return func0_word_len;
}