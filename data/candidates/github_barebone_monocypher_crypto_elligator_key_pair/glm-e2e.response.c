void crypto_elligator_key_pair(uint8_t *out_pub, uint8_t *out_priv, uint8_t *seed) {
    uint8_t buf[64];
    uint8_t priv[32];
    uint8_t tmp[32];

    // Loop 1: Copy the 32-byte seed into tmp
    for (size_t i = 0; i < 32; i++) {
        tmp[i] = seed[i];
    }

    // Loop 2: Generate key pair, retry if the inverse fails
    while (1) {
        // crypto_x25519_inverse(out=buf+32, in=buf, b=tmp[0])
        crypto_x25519_inverse(buf + 32, buf, tmp[0]);
        
        // crypto_x25519(out=priv, in=buf+32, basepoint=buf)
        crypto_x25519(priv, buf + 32, buf);
        
        // crypto_x25519_inverse(out=buf+32, in=priv, b=tmp[0])
        if (crypto_x25519_inverse(buf + 32, priv, tmp[0]) == 0) {
            break; // Success, exit the retry loop
        }
    }

    // Loop 3: Generate a new random 32-byte private key
    randombytes(seed, 32);

    // Loop 4: Copy tmp into out_pub
    for (size_t i = 0; i < 32; i++) {
        out_pub[i] = tmp[i];
    }

    // Loop 5: Copy buf into out_priv
    for (size_t i = 0; i < 32; i++) {
        out_priv[i] = buf[i];
    }

    // Securely wipe the local sensitive buffers
    wipe(buf, 64);
    wipe(priv, 32);
}