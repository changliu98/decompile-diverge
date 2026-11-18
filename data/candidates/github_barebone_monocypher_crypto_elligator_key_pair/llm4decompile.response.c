void crypto_elligator_key_pair(u8 hidden[32], u8 secret_key[32], u8 seed[32])
{
    u8 buf[64];
    u8 pk[32];
    int i;
    int ret;

    for (i = 0; i < 32; i++)
        buf[32 + i] = seed[i];

    do
    {
        crypto_chacha20_djb(buf, NULL, sizeof buf, buf + 32, "", 0);
        crypto_x25519_dirty_fast(pk, buf);
        ret = crypto_elligator_rev(buf + 32, pk, buf[32]);
    }
    while (ret != 0);

    crypto_wipe(seed, 32);

    for (i = 0; i < 32; i++)
        hidden[i] = buf[32 + i];

    for (i = 0; i < 32; i++)
        secret_key[i] = buf[i];

    crypto_wipe(buf, sizeof buf);
    crypto_wipe(pk, sizeof pk);
}