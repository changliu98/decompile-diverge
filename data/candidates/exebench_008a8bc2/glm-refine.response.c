int __cdecl obdRevConvert_42(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
    // Convert the floating point value to a scaled 16-bit integer
    int scaled_val = (int)(1000.0f * val);
    
    // Split the integer into high and low bytes (Big-Endian / network byte order)
    *A = (unsigned int)(scaled_val / 256);  // High byte
    *B = (unsigned int)(scaled_val % 256);  // Low byte
    
    // C and D are unused in this function
    (void)C;
    (void)D;
    
    return 2;
}