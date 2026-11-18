uint64_t crypto_chacha20_x(u8 *cipher_text,u8 *plain_text,size_t text_size,u8 *key,u8 *nonce,u64 ctr
                          )

{
  uint64_t uVar1;
  u8 sub_key [32];
  u64 ctr_local;
  u8 *nonce_local;
  u8 *key_local;
  size_t text_size_local;
  u8 *plain_text_local;
  u8 *cipher_text_local;
  
  crypto_chacha20_h(sub_key,key,nonce);
  uVar1 = crypto_chacha20_djb(cipher_text,plain_text,text_size,sub_key,nonce + 0x10,ctr);
  crypto_wipe(sub_key,0x20);
  return uVar1;
}