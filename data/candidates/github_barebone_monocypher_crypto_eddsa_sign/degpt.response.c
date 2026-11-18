void crypto_eddsa_sign(u8 *signature,u8 *secret_key,u8 *message,size_t message_size)

{
  size_t _i_;
  u8 R [32];
  u8 h [32];
  u8 r [32];
  u8 a [64];
  size_t message_size_local;
  u8 *message_local;
  u8 *secret_key_local;
  u8 *signature_local;
  
  crypto_blake2b(a,0x40,secret_key,0x20);
  crypto_eddsa_trim_scalar(a,a);
  hash_reduce(r,a + 0x20,0x20,message,message_size,(u8 *)0x0,0);
  crypto_eddsa_scalarbase(R,r);
  hash_reduce(h,R,0x20,secret_key + 0x20,0x20,message,message_size);
  for (_i_ = 0; _i_ < 0x20; _i_ = _i_ + 1) {
    signature[_i_] = R[_i_];
  }
  crypto_eddsa_mul_add(signature + 0x20,h,a,r);
  crypto_wipe(a,0x40);
  crypto_wipe(r,0x20);
  return;
}