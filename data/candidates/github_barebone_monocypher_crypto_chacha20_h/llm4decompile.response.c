void crypto_chacha20_h(u8 *out, const u8 *key, const u8 *in)
{
    u32 state[16];

    load32_le_buf(state, chacha20_constant, 4);
    load32_le_buf(state + 4, key, 8);
    load32_le_buf(state + 12, in, 4);

    chacha20_rounds(state, state);

    store32_le_buf(out, state, 4);
    store32_le_buf(out + 16, state + 12, 4);

    crypto_wipe(state, sizeof state);
}