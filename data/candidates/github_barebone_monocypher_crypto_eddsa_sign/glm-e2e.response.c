void crypto_eddsa_sign(uint8_t *sig, const uint8_t *secret_key, const uint8_t *msg, size_t msg_len) {
    uint8_t a[64];
    uint8_t r[32];
    uint8_t R[64];
    uint8_t h_ram[32];
    size_t i;

    // Hash the 64-byte secret key to expand it into scalar 'a' and nonce prefix
    crypto_blake2b(a, secret_key, 64, 64);

    // Clamp/trim the scalar
    crypto_eddsa_trim_scalar(a, a);

    // Generate nonce 'r' = hash_reduce(a[32..64], msg, 0, 0)
    hash_reduce(r, a + 32, 32, msg, msg_len, 0, 0);

    // Compute point R = r * B
    crypto_eddsa_scalarbase(R, r);

    // Compute challenge h_ram = hash_reduce(R, secret_key[32..64], msg, 0)
    hash_reduce(h_ram, R, 32, secret_key + 32, 32, 0, msg_len);

    // Copy the first 32 bytes of R into the signature
    for (i = 0; i < 32; i++) {
        sig[i] = R[i];
    }

    // Compute the scalar part of the signature: S = r + h_ram * a
    crypto_eddsa_mul_add(sig + 32, h_ram, a, r);

    // Securely wipe sensitive data from the stack
    crypto_wipe(a, 64);
    crypto_wipe(r, 32);
}