void squeeze_alt(char *s1, char *s2) {
    int i = 0;
    int j = 0;
    
    while (s1[i] != '\0') {
        int found = 0;
        int k = 0;
        
        while (s2[k] != '\0' && found != 1) {
            if (s1[i] == s2[k]) {
                found = 1;
            }
            k++;
        }
        
        if (found == 0) {
            s1[j] = s1[i];
            j++;
        }
        i++;
    }
    s1[j] = '\0';
}