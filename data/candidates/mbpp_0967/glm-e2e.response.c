const char* func0(const char* str) {
    const char* vowels = "aeiou";
    int count = 0;
    int seen[10];
    
    memset(seen, 0, sizeof(seen));
    
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; j < 10; j++) {
            if (str[i] == vowels[j]) {
                if (seen[j] == 0) {
                    seen[j] = 1;
                    count++;
                }
                break;
            }
        }
    }
    
    if (count >= 5) {
        return "YES";
    } else {
        return "NO";
    }
}