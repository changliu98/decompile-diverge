uint64_t __cdecl crypto_chacha20_djb(
        u8 *cipher_text,
        const u8 *plain_text,
        size_t text_size,
        const u8 *key,
        const u8 *nonce,
        u64 ctr)
{
  u32 v6; // eax
  u8 *out; // [rsp+8h] [rbp-138h]
  size_t i_1; // [rsp+10h] [rbp-130h]
  size_t i_0; // [rsp+18h] [rbp-128h]
  u8 tmp[64]; // [rsp+20h] [rbp-120h] BYREF
  u32 p_0; // [rsp+64h] [rbp-DCh]
  size_t j_0; // [rsp+68h] [rbp-D8h]
  u32 p; // [rsp+74h] [rbp-CCh]
  size_t j; // [rsp+78h] [rbp-C8h]
  size_t i; // [rsp+80h] [rbp-C0h]
  size_t nb_blocks; // [rsp+88h] [rbp-B8h]
  u32 pool[16]; // [rsp+90h] [rbp-B0h] BYREF
  u32 input[16]; // [rsp+D0h] [rbp-70h] BYREF
  u64 ctra; // [rsp+110h] [rbp-30h]
  const u8 *noncea; // [rsp+118h] [rbp-28h]
  const u8 *keya; // [rsp+120h] [rbp-20h]
  size_t text_sizea; // [rsp+128h] [rbp-18h]
  const u8 *plain_texta; // [rsp+130h] [rbp-10h]
  u8 *cipher_texta; // [rsp+138h] [rbp-8h]

  cipher_texta = cipher_text;
  plain_texta = plain_text;
  text_sizea = text_size;
  keya = key;
  noncea = nonce;
  ctra = ctr;
  load32_le_buf(input, chacha20_constant, 4uLL);
  load32_le_buf(&input[4], keya, 8uLL);
  load32_le_buf(&input[14], noncea, 2uLL);
  *(_QWORD *)&input[12] = ctra;
  nb_blocks = text_sizea >> 6;
  for ( i = 0LL; i < nb_blocks; ++i )
  {
    chacha20_rounds(pool, input);
    if ( plain_texta )
    {
      for ( j = 0LL; j < 0x10; ++j )
      {
        p = input[j] + pool[j];
        out = cipher_texta;
        v6 = load32_le(plain_texta);
        store32_le(out, v6 ^ p);
        cipher_texta += 4;
        plain_texta += 4;
      }
    }
    else
    {
      for ( j_0 = 0LL; j_0 < 0x10; ++j_0 )
      {
        p_0 = input[j_0] + pool[j_0];
        store32_le(cipher_texta, p_0);
        cipher_texta += 4;
      }
    }
    if ( !++input[12] )
      ++input[13];
  }
  text_sizea &= 0x3Fu;
  if ( text_sizea )
  {
    if ( !plain_texta )
      plain_texta = &zero;
    chacha20_rounds(pool, input);
    for ( i_0 = 0LL; i_0 < 0x10; ++i_0 )
      store32_le(&tmp[4 * i_0], input[i_0] + pool[i_0]);
    for ( i_1 = 0LL; i_1 < text_sizea; ++i_1 )
      cipher_texta[i_1] = plain_texta[i_1] ^ tmp[i_1];
    crypto_wipe(tmp, 0x40uLL);
  }
  ctra = (text_sizea != 0) + ((unsigned __int64)input[13] << 32) + input[12];
  crypto_wipe(pool, 0x40uLL);
  crypto_wipe(input, 0x40uLL);
  return ctra;
}