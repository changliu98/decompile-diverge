void __cdecl crypto_elligator_key_pair(u8 *hidden, u8 *secret_key, u8 *seed)
{
  u8 buf[64]; // [rsp+20h] [rbp-80h] BYREF
  u8 pk[32];  // [rsp+60h] [rbp-40h] BYREF
  size_t i;

  // Copy the 32-byte seed into the second half of buf
  memcpy(&buf[32], seed, 32);

  // Generate keys until elligator reverse mapping succeeds
  do
  {
    crypto_chacha20_djb(buf, 0LL, 64uLL, &buf[32], &zero, 0LL);
    crypto_x25519_dirty_fast(pk, buf);
  }
  while ( crypto_elligator_rev(&buf[32], pk, buf[32]) );

  // Securely wipe the original seed
  crypto_wipe(seed, 32uLL);

  // Output the hidden representation (from the second half of buf)
  memcpy(hidden, &buf[32], 32);

  // Output the secret key (from the first half of buf)
  memcpy(secret_key, buf, 32);

  // Securely wipe local buffers
  crypto_wipe(buf, 64uLL);
  crypto_wipe(pk, 32uLL);
}