uint64_t crypto_chacha20_x(void *out, const void *in, uint64_t in_len, 
                           const void *key, const void *nonce, uint64_t counter) {
    struct chacha20_ctx ctx;
    
    // 1ef0 - 1f1c: Call crypto_chacha20_h to initialize the local context
    crypto_chacha20_h(&ctx, key, nonce);
    
    // 1f21 - 1f3d: Call crypto_chacha20_djb to encrypt/decrypt the data
    // The nonce pointer is offset by 0x10 (16 bytes) as per the assembly
    uint64_t ret = crypto_chacha20_djb(out, in, in_len, &ctx, 
                                       (const struct chacha20_nonce *)((const uint8_t *)nonce + 0x10), 
                                       counter);
    
    // 1f46 - 1f4f: Securely wipe the local context (32 bytes)
    crypto_wipe(&ctx, 0x20);
    
    // 1f54 - 1f5d: Return the result and exit
    return ret;
}