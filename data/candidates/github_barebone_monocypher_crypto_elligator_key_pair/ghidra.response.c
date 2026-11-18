void crypto_elligator_key_pair(u8 *hidden,u8 *secret_key,u8 *seed)

{
  int iVar1;
  size_t _i__2;
  size_t _i__1;
  size_t _i_;
  u8 buf [64];
  u8 pk [32];
  u8 *seed_local;
  u8 *secret_key_local;
  u8 *hidden_local;
  
  for (_i_ = 0; _i_ < 0x20; _i_ = _i_ + 1) {
    buf[_i_ + 0x20] = seed[_i_];
  }
  do {
    crypto_chacha20_djb(buf,(u8 *)0x0,0x40,buf + 0x20,"",0);
    crypto_x25519_dirty_fast(pk,buf);
    iVar1 = crypto_elligator_rev(buf + 0x20,pk,buf[0x20]);
  } while (iVar1 != 0);
  crypto_wipe(seed,0x20);
  for (_i__1 = 0; _i__1 < 0x20; _i__1 = _i__1 + 1) {
    hidden[_i__1] = buf[_i__1 + 0x20];
  }
  for (_i__2 = 0; _i__2 < 0x20; _i__2 = _i__2 + 1) {
    secret_key[_i__2] = buf[_i__2];
  }
  crypto_wipe(buf,0x40);
  crypto_wipe(pk,0x20);
  return;
}