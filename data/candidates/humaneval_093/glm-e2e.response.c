void func0(char *input, char *output) {
    const char *key = "DUMMY";
    int i = 0;
    
    while (input[i] != '\0') {
        char c = input[i];
        
        if (isupper(c)) {
            c = toupper(c);
        } else if (islower(c)) {
            c = tolower(c);
        }
        
        int j = 0;
        while (key[j] != '\0') {
            if (c == key[j]) {
                if (j < 10) {
                    c += 2;
                }
                break;
            }
            j++;
        }
        
        output[i] = c;
        i++;
    }
    
    output[i] = '\0';
}