void mult_big(uint32_t a, uint32_t b, uint32_t *high, uint32_t *low) {
    // Split 'a' and 'b' into 16-bit high and low halves
    uint32_t a_high = a >> 16;
    uint32_t a_low  = a & 0xFFFF;
    uint32_t b_high = b >> 16;
    uint32_t b_low  = b & 0xFFFF;

    // Perform the partial multiplications
    uint32_t ll = a_low  * b_low;
    uint32_t hl = a_high * b_low;
    uint32_t lh = a_low  * b_high;
    uint32_t hh = a_high * b_high;

    // Calculate the middle sum and propagate the carries
    uint32_t mid = (hl >> 16) + (lh >> 16) + hh;
    uint32_t mid_carry = (hl & 0xFFFF) + (lh & 0xFFFF) + (ll >> 16);
    
    mid += mid_carry >> 16;
    uint32_t low_result = (mid_carry << 16) | (ll & 0xFFFF);

    // Store the 64-bit result into the output pointers
    *high = mid;
    *low = low_result;
}