void crypto_chacha20_ietf(u8 out[8], const u8 key[32], const u8 n[4])
{
    u32 state[16];
    load32_le_buf(state , chacha20_constant);
    load32_le_buf(state + 4, key );
    load32_le_buf(state + 12, n );
    chacha20_rounds(state, state);
    store32_le_buf(out , state );
    store32_le_buf(out + 4, state + 12);
    crypto_wipe(state, sizeof(state));
}