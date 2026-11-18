int FNEGQ(unsigned_long *result, unsigned_long *source)
{
    // Negate the sign bit of the first 64-bit word by XORing with 0x8000000000000000
    *result = *source ^ 0x8000000000000000;
    // Copy the second 64-bit word unchanged
    result[1] = source[1];
    // Return 1 to indicate success
    return 1;
}