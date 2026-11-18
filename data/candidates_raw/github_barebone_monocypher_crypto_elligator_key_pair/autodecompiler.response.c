void crypto_x25519_x25519(unsigned char *shared,
                          unsigned char *public_key,
                          unsigned char *secret_key)
{
    u8 e[64];
    u8 p[32];
    u8 s[32];
    u8 t[32];
    size_t i;
    for (i = 0; i < 32; ++i) {
        t[i] = secret_key[i];
    }
    crypto_wipe(t, 32);
    do {
        crypto_chacha20_djb(e, e, 64, e, zero, 0);
        crypto_x25519_dirty_fast(p, t);
    } while (crypto_elligator_rev(e + 32, p, e[32]) != 0);
    crypto_wipe(secret_key, 32);
    for (i = 0; i < 32; ++i) {
        shared[i] = e[i + 32];
    }
    for (i = 0; i < 32; ++i) {
        public_key[i] = e[i];
    }
    crypto_wipe(e, 64);
    crypto_wipe(p, 32);
}