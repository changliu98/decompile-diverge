void squeeze(char *s1, char *s2) {
    int i = 0;
    int j = 0;
    
    while (s1[i] != '\0') {
        int k = 0;
        char keep;
        
        while (s2[k] != '\0') {
            if (s1[i] == s2[k]) {
                keep = 0;
                break;
            }
            k++;
        }
        
        if (s2[k] == '\0') {
            s1[j] = s1[i];
            j++;
        }
        
        i++;
    }
    
    s1[j] = '\0';
}