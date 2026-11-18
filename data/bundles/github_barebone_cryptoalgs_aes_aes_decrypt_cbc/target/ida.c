int __cdecl aes_decrypt_cbc(const BYTE *in, size_t in_len, BYTE *out, const WORD *key, int keysize, const BYTE *iv)
{
  __int64 v6; // rcx
  BYTE *v7; // rax
  __int64 v8; // rcx
  int idx; // [rsp+8h] [rbp-78h]
  int blocks; // [rsp+Ch] [rbp-74h]
  BYTE iv_buf[16]; // [rsp+10h] [rbp-70h] BYREF
  BYTE buf_out[16]; // [rsp+20h] [rbp-60h] BYREF
  BYTE buf_in[16]; // [rsp+30h] [rbp-50h] BYREF
  const BYTE *iva; // [rsp+48h] [rbp-38h]
  int keysizea; // [rsp+54h] [rbp-2Ch]
  const WORD *keya; // [rsp+58h] [rbp-28h]
  BYTE *outa; // [rsp+60h] [rbp-20h]
  size_t in_lena; // [rsp+68h] [rbp-18h]
  const BYTE *ina; // [rsp+70h] [rbp-10h]

  ina = in;
  in_lena = in_len;
  outa = out;
  keya = key;
  keysizea = keysize;
  iva = iv;
  if ( (in_len & 0xF) != 0 )
    return 0;
  blocks = in_lena >> 4;
  *(_QWORD *)iv_buf = *(_QWORD *)iva;
  *(_QWORD *)&iv_buf[8] = *((_QWORD *)iva + 1);
  for ( idx = 0; idx < blocks; ++idx )
  {
    v6 = 16 * idx;
    *(_QWORD *)buf_in = *(_QWORD *)&ina[v6];
    *(_QWORD *)&buf_in[8] = *(_QWORD *)&ina[v6 + 8];
    aes_decrypt(buf_in, buf_out, keya, keysizea);
    xor_buf(iv_buf, buf_out, 0x10uLL);
    v7 = outa;
    v8 = 16 * idx;
    *(_QWORD *)&outa[v8] = *(_QWORD *)buf_out;
    *(_QWORD *)&v7[v8 + 8] = *(_QWORD *)&buf_out[8];
    *(_QWORD *)iv_buf = *(_QWORD *)buf_in;
    *(_QWORD *)&iv_buf[8] = *(_QWORD *)&buf_in[8];
  }
  return 1;
}