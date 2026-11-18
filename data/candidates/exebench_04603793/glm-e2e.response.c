void itoa(unsigned long value, char *str) {
    unsigned long temp = value;
    char *ptr = str;
    
    // Calculate the number of digits
    do {
        ptr++;
        temp /= 10;
    } while (temp != 0);
    
    // Null-terminate the string
    *ptr = '\0';
    
    // Convert digits to characters in reverse order
    do {
        unsigned long remainder = value % 10;
        *--ptr = (char)(remainder + '0');
        value /= 10;
    } while (value != 0);
}