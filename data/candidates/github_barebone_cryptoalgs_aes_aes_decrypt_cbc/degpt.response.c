int aes_decrypt_cbc(BYTE *ciphertext_input, size_t ciphertext_length, BYTE *plaintext_output, WORD *encryption_key, int key_bit_length, BYTE *initialization_vector)
{
    // Check if input length is a multiple of 16 bytes (AES block size)
    if ((ciphertext_length & 0xf) != 0) {
        return 0;
    }

    // Local buffers for IV and block processing
    BYTE working_iv[16];
    BYTE decrypted_block[16];
    BYTE current_ciphertext_block[16];

    // Initialize working IV with the provided initial vector
    memcpy(working_iv, initialization_vector, 16);

    // Process each 16-byte block
    for (size_t block_index = 0; block_index < ciphertext_length / 16; block_index++) {
        // Copy current ciphertext block to input buffer
        memcpy(current_ciphertext_block, ciphertext_input + (block_index << 4), 16);
        
        // Decrypt the block using AES
        aes_decrypt(current_ciphertext_block, decrypted_block, encryption_key, key_bit_length);
        
        // XOR decrypted output with previous ciphertext block (or IV for first block)
        xor_buf(working_iv, decrypted_block, 0x10);
        
        // Store the decrypted plaintext block
        memcpy(plaintext_output + (block_index << 4), decrypted_block, 16);
        
        // Update IV to current ciphertext block for next iteration (CBC mode)
        memcpy(working_iv, current_ciphertext_block, 16);
    }

    return 1;
}