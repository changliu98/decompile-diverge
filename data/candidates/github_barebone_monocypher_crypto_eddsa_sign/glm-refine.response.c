define 64_BYTES 64

void __cdecl crypto_eddsa_sign(u8 *signature, const u8 *secret_key, const u8 *message, size_t message_size)
{
  size_t i;
  u8 R[32_BYTES];
  u8 h[32_BYTES];
  u8 r[32_BYTES];
  u8 a[64_BYTES];

  // 1. Hash the secret key to generate the scalar `a` and the nonce prefix `a[32..63]`
  crypto_blake2b(a, 64_BYTES, secret_key, 32_BYTES);
  
  // 2. Clamp the scalar
  crypto_eddsa_trim_scalar(a, a);
  
  // 3. Generate the secret random `r` by hashing the nonce prefix and the message
  hash_reduce(r, &a[32_BYTES], 32_BYTES, message, message_size, 0LL, 0LL);
  
  // 4. Compute R = r * B (where B is the base point)
  crypto_eddsa_scalarbase(R, r);
  
  // 5. Compute the challenge hash h = SHA-512(R || public_key || message)
  hash_reduce(h, R, 32_BYTES, secret_key + 32_BYTES, 32_BYTES, message, message_size);
  
  // 6. The first half of the signature is R
  for (i = 0; i < 32_BYTES; ++i)
    signature[i] = R[i];
    
  // 7. The second half of the signature is S = h * a + r
  crypto_eddsa_mul_add(signature + 32_BYTES, h, a, r);
  
  // 8. Securely wipe sensitive data from the stack
  crypto_wipe(a, 64_BYTES);
  crypto_wipe(r, 32_BYTES);
}