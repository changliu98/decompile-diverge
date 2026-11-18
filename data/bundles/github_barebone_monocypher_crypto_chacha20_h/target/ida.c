void __cdecl crypto_chacha20_h(u8 *out, const u8 *key, const u8 *in)
{
  u32 block[16]; // [rsp+0h] [rbp-60h] BYREF
  const u8 *ina; // [rsp+48h] [rbp-18h]
  const u8 *keya; // [rsp+50h] [rbp-10h]
  u8 *outa; // [rsp+58h] [rbp-8h]

  outa = out;
  keya = key;
  ina = in;
  load32_le_buf(block, chacha20_constant, 4uLL);
  load32_le_buf(&block[4], keya, 8uLL);
  load32_le_buf(&block[12], ina, 4uLL);
  chacha20_rounds(block, block);
  store32_le_buf(outa, block, 4uLL);
  store32_le_buf(outa + 16, &block[12], 4uLL);
  crypto_wipe(block, 0x40uLL);
}