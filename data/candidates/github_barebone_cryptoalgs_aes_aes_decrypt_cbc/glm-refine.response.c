int __cdecl aes_decrypt_cbc(const BYTE *in, size_t in_len, BYTE *out, const WORD *key, int keysize, const BYTE *iv)
{
  BYTE iv_buf[16];
  BYTE buf_out[16];
  BYTE buf_in[16];
  int blocks;
  int idx;

  // Input length must be a multiple of the AES block size (16 bytes)
  if ((in_len & 0xF) != 0)
    return 0;

  blocks = in_len >> 4; // Number of 16-byte blocks
  
  // Initialize the running IV buffer
  memcpy(iv_buf, iv, 16);

  for (idx = 0; idx < blocks; ++idx)
  {
    // Load the current 16-byte block from input
    memcpy(buf_in, in + (16 * idx), 16);

    // Decrypt the block
    aes_decrypt(buf_in, buf_out, key, keysize);

    // XOR the decrypted block with the IV (or previous ciphertext block)
    // Note: Assuming xor_buf modifies the second argument in-place
    xor_buf(iv_buf, buf_out, 16);

    // Write the 16-byte plaintext block to output
    memcpy(out + (16 * idx), buf_out, 16);

    // The current input ciphertext block becomes the IV for the next block
    memcpy(iv_buf, buf_in, 16);
  }

  return 1;
}