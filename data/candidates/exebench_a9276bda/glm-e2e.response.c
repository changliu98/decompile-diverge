char* intToString(char* buffer, unsigned int num) {
    buffer[9] = '\0';
    int i = 8;
    
    while (i >= 0) {
        buffer[i] = (num % 10) + '0';
        num /= 10;
        if (num == 0) {
            break;
        }
        i--;
    }
    
    return &buffer[i];
}