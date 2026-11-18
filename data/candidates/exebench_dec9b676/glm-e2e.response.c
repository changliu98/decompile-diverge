void mult121665(int out[32], const int in[32]) {
    int carry = 0;
    int i;

    // First loop: Multiply each element by 121665 (0x1DB41) and propagate carry
    for (i = 0; i < 32; i++) {
        carry += in[i] * 0x1DB41;
        out[i] = carry & 0xFF;
        carry >>= 8;
    }

    // Process the 33rd element (index 32)
    carry += in[31] * 0x1DB41; // Note: Assembly accesses in+0x7c which is in[31]
    out[31] = carry & 0x7F;    // Note: Assembly accesses out+0x7c which is out[31]
    
    // Calculate the final carry to add back (multiply by 19, but assembly uses 0x13 = 19)
    carry = (carry >> 7) * 0x13;

    // Second loop: Add the carry back to the array
    for (i = 0; i < 32; i++) {
        carry += out[i];
        out[i] = carry & 0xFF;
        carry >>= 8;
    }

    // Final carry addition
    carry += out[31]; // Note: Assembly accesses out+0x7c which is out[31]
    out[31] = carry;
}