uint64_t __cdecl crypto_chacha20_x(
        u8 *cipher_text,
        const u8 *plain_text,
        size_t text_size,
        const u8 *key,
        const u8 *nonce,
        u64 ctr)
{
  u8 sub_key[32]; // [rsp+0h] [rbp-50h] BYREF
  u64 ctra; // [rsp+20h] [rbp-30h]
  const u8 *noncea; // [rsp+28h] [rbp-28h]
  const u8 *keya; // [rsp+30h] [rbp-20h]
  size_t text_sizea; // [rsp+38h] [rbp-18h]
  const u8 *plain_texta; // [rsp+40h] [rbp-10h]
  u8 *cipher_texta; // [rsp+48h] [rbp-8h]

  cipher_texta = cipher_text;
  plain_texta = plain_text;
  text_sizea = text_size;
  keya = key;
  noncea = nonce;
  ctra = ctr;
  crypto_chacha20_h(sub_key, key, nonce);
  ctra = crypto_chacha20_djb(cipher_texta, plain_texta, text_sizea, sub_key, noncea + 16, ctra);
  crypto_wipe(sub_key, 0x20uLL);
  return ctra;
}