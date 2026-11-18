void __cdecl mult_big(uint32_t a, uint32_t b, uint32_t *hi, uint32_t *lo)
{
    // Split the 32-bit inputs into 16-bit halves
    uint16_t a_lo = (uint16_t)a;
    uint16_t a_hi = (uint16_t)(a >> 16);
    uint16_t b_lo = (uint16_t)b;
    uint16_t b_hi = (uint16_t)(b >> 16);

    // Calculate the 4 partial 16-bit products
    uint32_t p0 = (uint32_t)b_lo * a_lo;
    uint32_t p1 = (uint32_t)b_lo * a_hi;
    uint32_t p2 = (uint32_t)b_hi * a_lo;
    uint32_t p3 = (uint32_t)b_hi * a_hi;

    // Calculate the middle 32-bit sum.
    // p0 >> 16 is the carry from the lowest 16 bits.
    // The (uint16_t) casts implicitly extract the lower 16 bits of p1 and p2.
    uint32_t mid_sum = (p0 >> 16) + (uint16_t)p1 + (uint16_t)p2;

    // The high 32 bits of the result:
    // - p3 contributes the highest 16 bits
    // - p1 >> 16 contributes the upper half of p1
    // - p2 >> 16 contributes the upper half of p2
    // - mid_sum >> 16 is the final carry from the middle calculation
    *hi = p3 + (p1 >> 16) + (p2 >> 16) + (mid_sum >> 16);

    // The low 32 bits of the result:
    // - (uint16_t)p0 is the lowest 16 bits
    // - (mid_sum << 16) shifts the middle sum up to occupy the upper 16 bits
    *lo = (uint16_t)p0 + (mid_sum << 16);
}