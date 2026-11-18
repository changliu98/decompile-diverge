int aes_decrypt_cbc_mac(byte *in, size_t in_len, byte *out, aes_ctx_t *ctx, int keysize, byte *iv)
{
 byte buf_in[16], buf_out[16], iv_buf[16];
 int blocks, idx;
 int ret;

 if (in_len % 16 != 0)
 {
  return(0);
 }

 blocks = in_len / 16;

 memcpy(iv_buf, iv, 16);

 for (idx = 0; idx < blocks; idx++)
 {

  memcpy(buf_in, &in[idx * 16], 16);


  ret = aes_decrypt(buf_in, buf_out, ctx, keysize);


  xor_buf(iv_buf, buf_out, 16);


  memcpy(&out[idx * 16], buf_out, 16);


  memcpy(iv_buf, buf_in, 16);
 }

 return(1);
}