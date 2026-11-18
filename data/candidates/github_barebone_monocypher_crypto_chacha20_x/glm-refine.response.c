uint64_t __cdecl crypto_chacha20_x(
        u8 *cipher_text,
        const u8 *plain_text,
        size_t text_size,
        const u8 *key,
        const u8 *nonce,
        u64 ctr)
{
  u8 sub_key[32];

  // Derive a subkey using the key and the first 16 bytes of the nonce
  crypto_chacha20_h(sub_key, key, nonce);

  // Encrypt the plaintext, passing the sub_key and the remaining nonce (offset by 16)
  ctr = crypto_chacha20_djb(cipher_text, plain_text, text_size, sub_key, nonce + 16, ctr);

  // Securely wipe the 32-byte sub_key from the stack
  crypto_wipe(sub_key, 32);

  return ctr;
}