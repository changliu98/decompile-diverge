char func0(char *str1) {
    int frequency[256];
    memset(frequency, 0, sizeof(frequency));
    int max_freq = 0;
    char max_char = 0;
    int len = strlen(str1);
    for (int i = 0; i < len; i++) {
        frequency[str1[i]]++;
        if (frequency[str1[i]] > max_freq) {
            max_freq = frequency[str1[i]];
            max_char = str1[i];
        }
    }
    return max_char;
}