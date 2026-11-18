uint32_t __cdecl gf_poly_mul2(uint32_t x)
{
    // Isolate the highest bit of each of the 4 packed bytes.
    // If a high bit is 1, multiplying by 27 (0x1B) applies the Galois Field 
    // reduction polynomial to that specific byte.
    uint32_t overflow = (x & 0x80808080) >> 7;
    uint32_t reduction = overflow * 27;

    // Isolate the lower 7 bits of each byte and shift them left by 1.
    // This performs the base "multiply by 2" operation.
    uint32_t shifted = (x & 0x7F7F7F7F) << 1; // equivalent to 2 * (x & 0x7F7F7F7F)

    // XOR the shifted values with the reduction polynomial where overflows occurred.
    return shifted ^ reduction;
}