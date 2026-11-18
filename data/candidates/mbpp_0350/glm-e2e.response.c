int func0(const char *str) {
    int max_freq = 0;
    int len = strlen(str);
    int freq[26];
    
    memset(freq, 0, 104); // 104 bytes = 26 * sizeof(int)
    
    for (int i = 0; i < len; i++) {
        freq[str[i] - 'a']++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }
    
    return len - max_freq;
}