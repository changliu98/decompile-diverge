void Swap8Bytes(unsigned char *p) {
    unsigned char temp;
    
    // Swap bytes 0 and 7
    temp = p[0];
    p[0] = p[7];
    p[7] = temp;
    
    // Swap bytes 1 and 6
    temp = p[1];
    p[1] = p[6];
    p[6] = temp;
    
    // Swap bytes 2 and 5
    temp = p[2];
    p[2] = p[5];
    p[5] = temp;
    
    // Swap bytes 3 and 4
    temp = p[3];
    p[3] = p[4];
    p[4] = temp;
}