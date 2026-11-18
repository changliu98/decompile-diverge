uint64_t __cdecl crypto_chacha20_djb(
        u8 *cipher_text,
        const u8 *plain_text,
        size_t text_size,
        const u8 *key,
        const u8 *nonce,
        u64 ctr)
{
    u32 pool[16];
    u32 input[16];
    u8 tmp[64];
    u8 *out = cipher_text;
    const u8 *in = plain_text;
    size_t rem = text_size;
    size_t nb_blocks = text_size >> 6; // 64 bytes per block

    // Initialize ChaCha20 state:
    // input[0..3]   = Constants ("expand 32-byte k")
    // input[4..11]  = Key
    // input[12..13] = Block counter (64-bit)
    // input[14..15] = Nonce
    load32_le_buf(input, chacha20_constant, 4);
    load32_le_buf(&input[4], key, 8);
    load32_le_buf(&input[14], nonce, 2);
    *(_QWORD *)&input[12] = ctr;

    // Process full 64-byte blocks
    for (size_t i = 0; i < nb_blocks; ++i)
    {
        chacha20_rounds(pool, input);
        
        if (in)
        {
            for (size_t j = 0; j < 16; ++j)
            {
                u32 keystream = input[j] + pool[j];
                u32 plain_word = load32_le(in);
                store32_le(out, plain_word ^ keystream);
                out += 4;
                in += 4;
            }
        }
        else
        {
            for (size_t j = 0; j < 16; ++j)
            {
                u32 keystream = input[j] + pool[j];
                store32_le(out, keystream);
                out += 4;
            }
        }
        
        // Increment 64-bit block counter (input[12] is low 32 bits, input[13] is high 32 bits)
        if (!++input[12])
            ++input[13];
    }

    // Process remaining bytes (partial block)
    rem &= 0x3F; // rem %= 64
    if (rem)
    {
        if (!in)
            in = &zero; // Use a zero buffer if plain_text was NULL (for PRNG mode)
            
        chacha20_rounds(pool, input);
        
        // Generate keystream into tmp buffer
        for (size_t i = 0; i < 16; ++i)
            store32_le(&tmp[4 * i], input[i] + pool[i]);
            
        // XOR remaining bytes
        for (size_t i = 0; i < rem; ++i)
            out[i] = in[i] ^ tmp[i];
            
        crypto_wipe(tmp, 64);
    }

    // Calculate final counter value
    uint64_t final_ctr = ((uint64_t)input[13] << 32) + input[12] + (rem != 0);

    // Securely wipe sensitive state from the stack
    crypto_wipe(pool, 64);
    crypto_wipe(input, 64);
    
    return final_ctr;
}