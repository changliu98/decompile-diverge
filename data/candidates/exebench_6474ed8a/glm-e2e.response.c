int gen256(unsigned char *arr, int param) {
    // Check if the 9th bit (0x100) of the parameter is set
    if ((param & 0x100) == 0) {
        return -1;
    }

    int key = param & 0xFF;
    int state = 1;
    
    arr[0] = 0;
    arr[1] = 1;

    for (int i = 2; i < 256; i++) {
        state <<= 1; // Multiply state by 2
        
        // If the 9th bit of state is set, XOR the lower 8 bits with the key
        if (state & 0x100) {
            state = (state & 0xFF) ^ key;
        }
        
        arr[i] = (unsigned char)state;
    }

    return 0;
}