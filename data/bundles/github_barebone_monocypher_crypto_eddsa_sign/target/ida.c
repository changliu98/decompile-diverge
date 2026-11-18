void __cdecl crypto_eddsa_sign(u8 *signature, const u8 *secret_key, const u8 *message, size_t message_size)
{
  size_t _i_; // [rsp+8h] [rbp-C8h]
  u8 R[32]; // [rsp+10h] [rbp-C0h] BYREF
  u8 h[32]; // [rsp+30h] [rbp-A0h] BYREF
  u8 r[32]; // [rsp+50h] [rbp-80h] BYREF
  u8 a[64]; // [rsp+70h] [rbp-60h] BYREF
  size_t message_sizea; // [rsp+B0h] [rbp-20h]
  const u8 *messagea; // [rsp+B8h] [rbp-18h]
  const u8 *secret_keya; // [rsp+C0h] [rbp-10h]
  u8 *signaturea; // [rsp+C8h] [rbp-8h]

  signaturea = signature;
  secret_keya = secret_key;
  messagea = message;
  message_sizea = message_size;
  crypto_blake2b(a, 0x40uLL, secret_key, 0x20uLL);
  crypto_eddsa_trim_scalar(a, a);
  hash_reduce(r, &a[32], 0x20uLL, messagea, message_sizea, 0LL, 0LL);
  crypto_eddsa_scalarbase(R, r);
  hash_reduce(h, R, 0x20uLL, secret_keya + 32, 0x20uLL, messagea, message_sizea);
  for ( _i_ = 0LL; _i_ < 0x20; ++_i_ )
    signaturea[_i_] = R[_i_];
  crypto_eddsa_mul_add(signaturea + 32, h, a, r);
  crypto_wipe(a, 0x40uLL);
  crypto_wipe(r, 0x20uLL);
}