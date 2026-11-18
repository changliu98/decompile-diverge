void murcielagoCrypt(char *str) {
    const char *key1 = "murcielago";
    const char *key2 = "0123456789";
    int i = 0;
    
    // Loop until the null terminator of the input string
    while (str[i] != '\0') {
        int j = 0;
        
        // Loop through the characters of key1 ("murcielago")
        while (key1[j] != '\0') {
            // If the current character in the string matches a character in key1
            if (str[i] == key1[j]) {
                // Replace it with the corresponding character in key2 ("0123456789")
                str[i] = key2[j];
                break;
            }
            j++;
        }
        i++;
    }
}