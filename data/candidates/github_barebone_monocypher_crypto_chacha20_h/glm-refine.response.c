void __cdecl crypto_chacha20_h(u8 *out, const u8 *key, const u8 *in)
{
  u32 block[16]; // [rsp+0h] [rbp-60h] BYREF

  // Load the ChaCha20 state matrix:
  // block[0..3]   = Constants ("expand 32-byte k")
  // block[4..11]  = 256-bit Key
  // block[12..15] = 128-bit Input (Nonce/Counter)
  load32_le_buf(block, chacha20_constant, 4uLL);
  load32_le_buf(&block[4], key, 8uLL);
  load32_le_buf(&block[12], in, 4uLL);

  // Perform the ChaCha20 block function (20 rounds)
  chacha20_rounds(block, block);

  // Serialize the output:
  // Write block[0..3] to the first 16 bytes
  store32_le_buf(out, block, 4uLL);
  // Write block[12..15] to the next 16 bytes
  store32_le_buf(out + 16, &block[12], 4uLL);

  // Securely wipe the state from the stack
  crypto_wipe(block, 0x40uLL); // 0x40 = 64 bytes
}