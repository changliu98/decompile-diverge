void strrev(char *str) {
    int i = 0;
    int j;
    char temp;

    // Find the length of the string
    while (str[i] != '\0') {
        i++;
    }
    
    // Set j to the index of the last character
    j = i - 1;
    i = 0; // Reset i to 0 for the start of the string

    // Swap characters from the ends towards the center
    while (i < j) {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        
        j--;
        i++;
    }
}