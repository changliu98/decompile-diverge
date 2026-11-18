int c_insensitive(char *s1, char *s2) {
    int i = 0;
    
    // Convert s1 to uppercase
    while (s1[i] != '\0') {
        if (s1[i] > 0x60 && s1[i] < 0x7b) {
            s1[i] -= 0x20;
        }
        i++;
    }
    
    i = 0;
    // Convert s2 to uppercase
    while (s2[i] != '\0') {
        if (s2[i] > 0x60 && s2[i] < 0x7b) {
            s2[i] -= 0x20;
        }
        i++;
    }
    
    i = 0;
    // Compare the two strings
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] > s2[i]) {
            return 1;
        } else if (s1[i] < s2[i]) {
            return -1;
        }
        i++;
    }
    
    return 0;
}