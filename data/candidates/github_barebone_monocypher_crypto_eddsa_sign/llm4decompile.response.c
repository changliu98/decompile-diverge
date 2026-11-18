void crypto_eddsa_sign(unsigned char *signature,
                       const unsigned char *secret_key,
                       const unsigned char *message,
                       size_t message_size)
{
    unsigned char d[64], h[32], r[32];
    crypto_uint32 i;

    crypto_blake2b(d, sizeof(d), secret_key, 32);
    crypto_eddsa_trim_scalar(d, d);

    hash_reduce(r, d + 32, 32, message, message_size, NULL, 0);
    crypto_eddsa_scalarbase(signature, r);

    hash_reduce(h, signature, 32, secret_key + 32, 32, message, message_size);

    for (i = 0; i < 32; ++i)
        signature[32 + i] = signature[i];
    crypto_eddsa_mul_add(signature + 32, h, d, r);

    crypto_wipe(d, sizeof(d));
    crypto_wipe(r, sizeof(r));
}