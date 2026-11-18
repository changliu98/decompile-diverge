int __cdecl obdRevConvert_0C(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
    // Calculate the scaled value once to avoid redundant computation
    int scaled_val = (int)(4.0f * val);

    // Extract the high byte and low byte
    *A = (unsigned int)(scaled_val / 256);
    *B = (unsigned int)(scaled_val % 256);

    // Unused parameters
    (void)C;
    (void)D;

    return 2;
}