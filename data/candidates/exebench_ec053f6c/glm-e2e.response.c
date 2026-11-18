void swapIntEndian(int *ptr) {
    char *bytes = (char *)ptr;
    
    // Swap byte 0 and byte 3
    char temp = bytes[0];
    bytes[0] = bytes[3];
    bytes[3] = temp;
    
    // Swap byte 1 and byte 2
    temp = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = temp;
}