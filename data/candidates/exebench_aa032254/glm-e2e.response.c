void i8253_cascade_ns_to_timer_power(int base, uint32_t *d1, uint32_t *d2, uint32_t *d3, int flags) {
    int div1 = 2;
    int div2;
    int base_mul_div1;
    int masked_flags;
    int temp;

    while (div1 <= 0x10000) {
        base_mul_div1 = base * div1;
        masked_flags = flags & 0x30000;
        
        if (masked_flags == 0x10000) {
            div2 = *d3 / base_mul_div1;
        } else if (masked_flags == 0x20000) {
            div2 = (*d3 + base_mul_div1 - 1) / base_mul_div1;
        } else {
            // Handles masked_flags == 0 and masked_flags == 0x30000
            div2 = (*d3 + base_mul_div1 / 2) / base_mul_div1;
        }

        if (div2 < 2) {
            div2 = 2;
        }

        if (div2 <= 0x10000) {
            *d3 = div2 * base_mul_div1;
            *d1 = div1 & 0xffff;
            *d2 = div2 & 0xffff;
            return;
        }

        div1 <<= 1;
    }

    div1 = 0x10000;
    div2 = 0x10000;
    *d3 = div1 * div2 * base;
    *d1 = div1 & 0xffff;
    *d2 = div2 & 0xffff;
}