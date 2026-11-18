void __cdecl crypto_elligator_key_pair(u8 *hidden, u8 *secret_key, u8 *seed)
{
  size_t _i__1; // [rsp+8h] [rbp-98h]
  size_t _i__0; // [rsp+10h] [rbp-90h]
  size_t _i_; // [rsp+18h] [rbp-88h]
  u8 buf[64]; // [rsp+20h] [rbp-80h] BYREF
  u8 pk[32]; // [rsp+60h] [rbp-40h] BYREF
  u8 *seeda; // [rsp+88h] [rbp-18h]
  u8 *secret_keya; // [rsp+90h] [rbp-10h]
  u8 *hiddena; // [rsp+98h] [rbp-8h]

  hiddena = hidden;
  secret_keya = secret_key;
  seeda = seed;
  for ( _i_ = 0LL; _i_ < 0x20; ++_i_ )
    buf[_i_ + 32] = seeda[_i_];
  do
  {
    crypto_chacha20_djb(buf, 0LL, 0x40uLL, &buf[32], &zero, 0LL);
    crypto_x25519_dirty_fast(pk, buf);
  }
  while ( crypto_elligator_rev(&buf[32], pk, buf[32]) );
  crypto_wipe(seeda, 0x20uLL);
  for ( _i__0 = 0LL; _i__0 < 0x20; ++_i__0 )
    hiddena[_i__0] = buf[_i__0 + 32];
  for ( _i__1 = 0LL; _i__1 < 0x20; ++_i__1 )
    secret_keya[_i__1] = buf[_i__1];
  crypto_wipe(buf, 0x40uLL);
  crypto_wipe(pk, 0x20uLL);
}