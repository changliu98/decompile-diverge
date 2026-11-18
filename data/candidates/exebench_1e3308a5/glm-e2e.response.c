void neg_s(float *a, float *b) {
    // Read the float from the first pointer
    float val = *a;
    
    // Type-pun the float to an unsigned 32-bit integer to manipulate its bits
    unsigned int bits = *(unsigned int *)&val;
    
    // Toggle the sign bit (MSB) using XOR
    bits ^= 0x80000000;
    
    // Type-pun back to float
    float neg_val = *(float *)&bits;
    
    // Store the result into the second pointer
    *b = neg_val;
}