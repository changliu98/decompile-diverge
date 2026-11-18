uint64_t crypto_chacha20_x(u8 *ciphertext, u8 *plaintext, size_t length, u8 *master_key, u8 *nonce, u64 ctr)
{
  u8 sub_key[32];
  // Derive the sub-key from the main key and nonce
  crypto_chacha20_h(sub_key, key, nonce);
  // Perform the ChaCha20 encryption/decryption using the derived sub-key and extended nonce
  uint64_t result = crypto_chacha20_djb(cipher_text, plain_text, text_size, sub_key, nonce + 0x10, ctr);
  // Securely wipe the sub-key from memory to prevent leakage
  crypto_wipe(sub_key, 0x20);
  return result;
}