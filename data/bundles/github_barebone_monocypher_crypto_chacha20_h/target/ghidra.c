void crypto_chacha20_h(u8 *out,u8 *key,u8 *in)

{
  u32 block [16];
  u8 *in_local;
  u8 *key_local;
  u8 *out_local;
  
  load32_le_buf(block,chacha20_constant,4);
  load32_le_buf(block + 4,key,8);
  load32_le_buf(block + 0xc,in,4);
  chacha20_rounds(block,block);
  store32_le_buf(out,block,4);
  store32_le_buf(out + 0x10,block + 0xc,4);
  crypto_wipe(block,0x40);
  return;
}