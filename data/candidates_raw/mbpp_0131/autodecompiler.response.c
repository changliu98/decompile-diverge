char* func0(char* input_string) {
    char vowels[100];
    int i, j = 0;
    memset(vowels, 0, sizeof(vowels));
    for (i = 0;; i++) {
        if (*(input_string + i) == '\0') {
            break;
        }
        char current_char = *(input_string + i);
        if (strchr("aeiouAEIOU", current_char)) {
            *(vowels + j++) = current_char;
        }
    }
    *(vowels + j) = '\0';
    j = 0;
    int k = strlen(vowels) - 1;
    for (i = 0;; i++) {
        if (*(input_string + i) == '\0') {
            break;
        }
        char current_char = *(input_string + i);
        if (strchr("aeiouAEIOU", current_char)) {
            *(func0_result_string + j++) = *(vowels + k--);
        } else {
            *(func0_result_string + j++) = *(input_string + i);
        }
    }
    *(func0_result_string + j) = '\0';
    return func0_result_string;
}