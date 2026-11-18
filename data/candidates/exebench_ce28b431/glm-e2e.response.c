void swap_int(int *a) {
    char *bytes = (char *)a;
    
    // Swap byte 0 and byte 3
    char temp1 = bytes[0];
    bytes[0] = bytes[3];
    bytes[3] = temp1;
    
    // Swap byte 1 and byte 2
    char temp2 = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = temp2;
}