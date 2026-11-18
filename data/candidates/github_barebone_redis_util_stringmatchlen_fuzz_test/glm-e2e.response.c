int stringmatchlen_fuzz_test() {
    int iterations = 10000000;
    int sum = 0;
    
    while (iterations-- > 0) {
        int pattern_len = rand() & 0x1f;
        int string_len = rand() & 0x1f;
        
        char pattern[32];
        for (int i = 0; i < pattern_len; i++) {
            pattern[i] = rand() % 128;
        }
        
        char string[32];
        for (int i = 0; i < string_len; i++) {
            string[i] = rand() % 128;
        }
        
        sum += stringmatchlen(pattern, pattern_len, string, string_len, 0);
    }
    
    return sum;
}