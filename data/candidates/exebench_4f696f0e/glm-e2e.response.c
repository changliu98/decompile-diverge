void SwapIEEE32(unsigned char *p) {
    unsigned char temp;
    
    // Swap byte 0 and byte 3
    temp = p[0];
    p[0] = p[3];
    p[3] = temp;
    
    // Swap byte 1 and byte 2
    temp = p[1];
    p[1] = p[2];
    p[2] = temp;
}