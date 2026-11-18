int aes_decrypt_cbc(const uint8_t *in, uint64_t in_len, uint8_t *out, const void *key, int bits, const uint8_t *iv) {
    // Check if input length is a multiple of 16 bytes (AES block size)
    if ((in_len & 0xf) != 0) {
        return 0;
    }

    uint64_t num_blocks = in_len >> 4; // Equivalent to in_len / 16
    
    // Store the IV into a local 16-byte buffer
    uint8_t prev_block[16];
    memcpy(prev_block, iv, 16);

    for (uint64_t i = 0; i < num_blocks; i++) {
        uint8_t current_block[16];
        uint8_t decrypted_block[16];

        // Copy current block from input
        memcpy(current_block, in + (i * 16), 16);

        // Decrypt the current block
        aes_decrypt(current_block, decrypted_block, key, bits);

        // XOR the decrypted block with the previous ciphertext block (or IV)
        xor_buf(prev_block, decrypted_block, 16);

        // Write the result to the output buffer
        memcpy(out + (i * 16), decrypted_block, 16);

        // Update prev_block to be the current ciphertext block for the next iteration
        memcpy(prev_block, current_block, 16);
    }

    return 1;
}