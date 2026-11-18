void expand(char *s1, char *s2) {
    // Check for digits range (e.g., "0-9")
    if (s1[0] >= '0' && s1[0] <= '9' && 
        s1[2] >= '0' && s1[2] <= '9' && 
        s1[0] <= s1[2]) {
        
        char c = s1[0];
        int i = 0;
        while (c <= s1[2]) {
            s2[i++] = c++;
        }
        s2[i] = '\0';
    } 
    // Check for uppercase letters range (e.g., "A-Z")
    else if (s1[0] >= 'A' && s1[0] <= 'Z' && 
             s1[2] >= 'A' && s1[2] <= 'Z' && 
             s1[0] <= s1[2]) {
        
        char c = s1[0];
        int i = 0;
        while (c <= s1[2]) {
            s2[i++] = c++;
        }
        s2[i] = '\0';
    } 
    // Check for lowercase letters range (e.g., "a-z")
    else if (s1[0] >= 'a' && s1[0] <= 'z' && 
             s1[2] >= 'a' && s1[2] <= 'z' && 
             s1[0] <= s1[2]) {
        
        char c = s1[0];
        int i = 0;
        while (c <= s1[2]) {
            s2[i++] = c++;
        }
        s2[i] = '\0';
    }
}