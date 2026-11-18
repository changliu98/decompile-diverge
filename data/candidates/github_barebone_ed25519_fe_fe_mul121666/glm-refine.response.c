void __cdecl fe_mul121666(int32_t *h, int32_t *f)
{
    int64_t h_even, h_odd;
    int32_t carry_odd, carry_even;
    int32_t f_odd[5];
    
    // Cache odd-indexed elements to avoid repeated memory lookups
    for (int i = 0; i < 5; i++) {
        f_odd[i] = f[2 * i + 1];
    }

    // h0 = f[0] * 121666 + 19 * carry(f[9] * 121666)
    h_odd = 121666LL * f[0] + 19LL * CARRY_25(121666LL * f_odd[4]);
    carry_even = CARRY_26(h_odd);
    h[0] = (int32_t)h_odd - (carry_even << 26);

    // Process limbs 1 through 8
    for (int i = 0; i < 4; i++) {
        // Odd index (1, 3, 5, 7)
        h_odd = 121666LL * f_odd[i] + carry_even;
        carry_odd = CARRY_25(h_odd);
        h[2 * i + 1] = (int32_t)h_odd - (carry_odd << 25) + carry_even;

        // Even index (2, 4, 6, 8)
        h_even = 121666LL * f[2 * i + 2] + carry_odd;
        carry_even = CARRY_26(h_even);
        h[2 * i + 2] = (int32_t)h_even - (carry_even << 26);
    }

    // Process limb 9
    h_odd = 121666LL * f_odd[4] + carry_even;
    carry_odd = CARRY_25(h_odd);
    h[9] = (int32_t)h_odd - (carry_odd << 25) + carry_even;
}