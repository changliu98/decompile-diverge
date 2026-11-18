char * reverse(char line[]) {
    char * words[10];
    int word_count = 0;
    char * word = strtok(line, " ");
    while (true) {
        if (word == NULL) {
            break;
        }
        words[word_count++] = word;
        word = strtok(NULL, " ");
    }

    func0_result[0] = '\0';
    for (int i = word_count - 1; ; --i) {
        if (i < 0) {
            break;
        }
        strcat(func0_result, words[i]);
        if (i > 0) {
            strcat(func0_result, " ");
        }
    }
    return func0_result;
}