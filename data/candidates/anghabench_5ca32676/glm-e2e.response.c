void wht4x4(int16_t *a) {
    // First pass: process rows
    for (int i = 0; i < 4; i++) {
        int32_t a0 = a[i * 4 + 0];
        int32_t a1 = a[i * 4 + 1];
        int32_t a2 = a[i * 4 + 2];
        int32_t a3 = a[i * 4 + 3];

        a0 += a1;
        a3 = a3 - a2;
        int32_t tmp = (a0 - a3) >> 1;
        a1 = tmp - a1;
        a2 = tmp - a2;
        a0 = a0 - a2;
        a3 = a3 + a1;

        a[i * 4 + 0] = (int16_t)a0;
        a[i * 4 + 1] = (int16_t)a2;
        a[i * 4 + 2] = (int16_t)a3;
        a[i * 4 + 3] = (int16_t)a1;
    }

    // Second pass: process columns
    for (int i = 0; i < 4; i++) {
        int32_t a0 = a[i + 0];
        int32_t a1 = a[i + 4];
        int32_t a2 = a[i + 8];
        int32_t a3 = a[i + 12];

        a0 += a1;
        a3 = a3 - a2;
        int32_t tmp = (a0 - a3) >> 1;
        a1 = tmp - a1;
        a2 = tmp - a2;
        a0 = a0 - a2;
        a3 = a3 + a1;

        // Note: The final results are scaled by 2 (left shift by 1)
        a[i + 0]  = (int16_t)(a0 << 1);
        a[i + 4]  = (int16_t)(a2 << 1);
        a[i + 8]  = (int16_t)(a3 << 1);
        a[i + 12] = (int16_t)(a1 << 1);
    }
}