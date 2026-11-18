void word2string(int value, char *str) {
    char *ptr = str;
    
    if (value == 0) {
        *(int*)ptr = 0x2030;  // Writes "0 " (little-endian: '0', ' ', '\0', '\0')
        return;
    }
    
    for (int i = 0; i < 6; i++) {
        int divisor = word2string._smth[i];
        int quotient = value / divisor;
        
        if (ptr == str) {
            // If it's the first character and the quotient is 0, skip writing '0'
            if (quotient == 0) {
                continue;
            }
        }
        
        *ptr = (char)(quotient + '0');
        ptr++;
        
        value %= divisor;
    }
    
    *ptr = ' '; // Appends a trailing space
}