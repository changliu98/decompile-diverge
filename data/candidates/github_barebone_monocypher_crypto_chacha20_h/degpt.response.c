void crypto_chacha20_h(u8 *output_buffer, u8 *encryption_key, u8 *nonce)
{
    u32 state_block[16];

    // Load ChaCha20 constants into the first 4 words of the state block
    load32_le_buf(state_block, chacha_constants, 4);
    
    // Load the 8-byte key into words 4 and 5 of the state block
    load32_le_buf(state_block + 4, encryption_key, 8);
    
    // Load the 4-byte input (nonce/counter) into words 12 and 13 of the state block
    load32_le_buf(state_block + 0xc, nonce, 4);
    
    // Perform 20 rounds of ChaCha20 mixing on the state block
    chacha20_mix(state_block, state_block);
    
    // Store the first 4 words of the resulting state to the output buffer
    store32_le_buf(output_buffer, state_block, 4);
    
    // Store words 12 and 13 of the resulting state to the output buffer (offset 0x10)
    store32_le_buf(output_buffer + 0x10, state_block + 0xc, 4);
    
    // Securely wipe the temporary state block from memory to prevent leakage
    secure_memset(state_block, 0x40);
}