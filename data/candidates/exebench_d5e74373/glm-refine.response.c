int __cdecl obdRevConvert_3C_3F(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
    // The formula scales the input value by shifting it by +40, then multiplying by 10.
    // This maps the range [-40.0, 215.0] to [0, 2550].
    float scaled_val = 10.0f * (val + 40.0f);

    // Cast to integer to extract the 16-bit payload
    int raw_val = (int)scaled_val;

    // Split the 16-bit integer into two 8-bit bytes (Big-Endian / MSB first)
    if (A) *A = (unsigned int)(raw_val / 256); // Equivalent to (raw_val >> 8) & 0xFF
    if (B) *B = (unsigned int)(raw_val % 256); // Equivalent to raw_val & 0xFF

    // C and D are unused in this conversion routine
    return 2;
}