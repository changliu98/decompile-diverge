16

int __cdecl unicoder_utf16_decode(unsigned int *result, const unsigned __int8 *p, unsigned int endianness)
{
    uint16_t dbyteA, dbyteB;

    // Validate endianness (1 = Little Endian, 2 = Big Endian)
    if (endianness != 1 && endianness != 2)
        return ERR_INVALID_ENDIANNESS;

    // Validate pointers
    if (!p || !result)
        return ERR_NULL_POINTER;

    // Extract the two 16-bit code units based on endianness
    if (endianness == 1) {
        // Little Endian
        dbyteA = *(const uint16_t *)p;
        dbyteB = *(const uint16_t *)(p + 2);
    } else {
        // Big Endian
        dbyteA = (p[0] << 8) | p[1];
        dbyteB = (p[2] << 8) | p[3];
    }

    // Check for UTF-16 Surrogate Pairs
    if (dbyteA >= 0xD800 && dbyteA <= 0xDFFF) {
        // dbyteA must be a High Surrogate
        if (dbyteA > 0xDBFF)
            return ERR_INVALID_SURROGATE;

        // dbyteB must be a Low Surrogate
        if (dbyteB < 0xDC00 || dbyteB > 0xDFFF)
            return ERR_INVALID_SURROGATE;

        // Combine the surrogate pair into a single 21-bit codepoint
        *result = 0x10000 + ((dbyteA & 0x3FF) << 10) + (dbyteB & 0x3FF);
        return 4; // Consumed 4 bytes
    } 
    else if (dbyteA <= 0x10FFFF) {
        // Single 16-bit code unit (Basic Multilingual Plane)
        *result = dbyteA;
        return 2; // Consumed 2 bytes
    } 
    else {
        // Out of valid Unicode range
        return ERR_CODEPOINT_TOO_LARGE;
    }
}