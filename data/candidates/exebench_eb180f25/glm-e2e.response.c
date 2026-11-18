double Mat_doubleSwap(double *p) {
    double val = *p;
    char *bytes = (char *)&val;
    
    // Swap bytes 0 and 7
    bytes[0] ^= bytes[7];
    bytes[7] ^= bytes[0];
    bytes[0] ^= bytes[7];
    
    // Swap bytes 1 and 6
    bytes[1] ^= bytes[6];
    bytes[6] ^= bytes[1];
    bytes[1] ^= bytes[6];
    
    // Swap bytes 2 and 5
    bytes[2] ^= bytes[5];
    bytes[5] ^= bytes[2];
    bytes[2] ^= bytes[5];
    
    // Swap bytes 3 and 4
    bytes[3] ^= bytes[4];
    bytes[4] ^= bytes[3];
    bytes[3] ^= bytes[4];
    
    *p = val;
    return val;
}