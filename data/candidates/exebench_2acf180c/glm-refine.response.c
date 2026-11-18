void __cdecl unpackFloat(const float aV, int *exponent, int *magnitude)
{
    // Reinterpret the float's bit pattern as an unsigned 32-bit integer
    uint32_t bits = *(uint32_t *)&aV;

    // Extract the 8-bit exponent (bits 23-30), shift it down, and unbias it
    *exponent = ((bits & 0x7F800000) >> 23) - 127;

    // Extract the 23-bit mantissa (bits 0-22) and add the implicit leading 1
    *magnitude = (bits & 0x7FFFFF) + 0x800000;

    // Apply the sign bit
    if (aV < 0.0f)
    {
        *magnitude = -*magnitude;
    }
}