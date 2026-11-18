static void tea_decrypt(uint32_t state[4], uint32_t const in[12])
{
    uint32_t W[16];
    uint32_t A, B, C, D;
    size_t i;

    A = state[0];
    B = state[1];
    C = state[2];
    D = state[3];

    for (i = 0; i < 16; i++) {
        W[i] = in[i];
    }

    for (i = 0; i < 32; i++) {
        uint32_t temp;

        temp = A;
        A = B ^ F1(B, C, D) + E1(A, B, C, D) + W[(i + 0) % 16];
        D = temp;

        temp = B;
        B = C ^ F2(A, B, C, D) + E2(A, B, C, D) + W[(i + 4) % 16];
        C = temp;
    }

    state[0] = A;
    state[1] = B;
    state[2] = C;
    state[3] = D;
}