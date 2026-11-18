uint64_t crypto_chacha20_djb(u8 *cipher_text,u8 *plain_text,size_t text_size,u8 *key,u8 *nonce,
                            u64 ctr)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  ulong uVar4;
  size_t i_2;
  size_t i_1;
  u8 tmp [64];
  u32 p_1;
  size_t j_1;
  u32 p;
  size_t j;
  size_t i;
  size_t nb_blocks;
  u32 pool [16];
  u32 input [16];
  u64 ctr_local;
  u8 *nonce_local;
  u8 *key_local;
  size_t text_size_local;
  u8 *plain_text_local;
  u8 *cipher_text_local;
  
  load32_le_buf(input,chacha20_constant,4);
  load32_le_buf(input + 4,key,8);
  load32_le_buf(input + 0xe,nonce,2);
  plain_text_local = plain_text;
  cipher_text_local = cipher_text;
  for (i = 0; input._48_8_ = ctr, i < text_size >> 6; i = i + 1) {
    chacha20_rounds(pool,input);
    if (plain_text_local == (u8 *)0x0) {
      for (j_1 = 0; j_1 < 0x10; j_1 = j_1 + 1) {
        store32_le(cipher_text_local,pool[j_1] + input[j_1]);
        cipher_text_local = cipher_text_local + 4;
      }
    }
    else {
      for (j = 0; j < 0x10; j = j + 1) {
        uVar1 = pool[j];
        uVar2 = input[j];
        uVar3 = load32_le(plain_text_local);
        store32_le(cipher_text_local,uVar1 + uVar2 ^ uVar3);
        cipher_text_local = cipher_text_local + 4;
        plain_text_local = plain_text_local + 4;
      }
    }
    if (input[0xc] + 1 == 0) {
      input[0xd] = input[0xd] + 1;
    }
    ctr = CONCAT44(input[0xd],input[0xc] + 1);
  }
  uVar4 = text_size & 0x3f;
  if (uVar4 != 0) {
    if (plain_text_local == (u8 *)0x0) {
      plain_text_local = "";
    }
    chacha20_rounds(pool,input);
    for (i_1 = 0; i_1 < 0x10; i_1 = i_1 + 1) {
      store32_le(tmp + i_1 * 4,pool[i_1] + input[i_1]);
    }
    for (i_2 = 0; i_2 < uVar4; i_2 = i_2 + 1) {
      cipher_text_local[i_2] = tmp[i_2] ^ plain_text_local[i_2];
    }
    crypto_wipe(tmp,0x40);
    ctr = input._48_8_;
  }
  input._48_8_ = ctr;
  crypto_wipe(pool,0x40);
  crypto_wipe(input,0x40);
  return ctr + (long)(int)(uint)(uVar4 != 0);
}