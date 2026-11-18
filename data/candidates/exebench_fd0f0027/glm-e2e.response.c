void ltostr(unsigned int num, char *str) {
    str[0] = '\0';
    str[8] = '\0';
    
    for (int i = 0; i < 8; i++) {
        int digit = num & 0xf;
        digit += 0x30; // '0'
        
        if (digit >= 0x3a) { // '9' + 1
            digit += 7;      // Shift to 'A' - 'F'
        }
        
        str[7 - i] = (char)digit;
        num >>= 4;
    }
}