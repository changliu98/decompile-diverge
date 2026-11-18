int aes_decrypt_cbc(BYTE *in,size_t in_len,BYTE *out,WORD *key,int keysize,BYTE *iv)

{
  int idx;
  int blocks;
  BYTE iv_buf [16];
  BYTE buf_out [16];
  BYTE buf_in [16];
  BYTE *iv_local;
  int keysize_local;
  WORD *key_local;
  BYTE *out_local;
  size_t in_len_local;
  BYTE *in_local;
  int local_c;
  
  if ((in_len & 0xf) == 0) {
    iv_buf._0_8_ = *(undefined8 *)iv;
    iv_buf._8_8_ = *(undefined8 *)(iv + 8);
    for (idx = 0; idx < (int)(in_len >> 4); idx = idx + 1) {
      buf_in._0_8_ = *(undefined8 *)(in + (idx << 4));
      buf_in._8_8_ = *(undefined8 *)(in + (long)(idx << 4) + 8);
      aes_decrypt(buf_in,buf_out,key,keysize);
      xor_buf(iv_buf,buf_out,0x10);
      *(undefined8 *)(out + (idx << 4)) = buf_out._0_8_;
      *(undefined8 *)(out + (long)(idx << 4) + 8) = buf_out._8_8_;
      iv_buf[0] = buf_in[0];
      iv_buf[1] = buf_in[1];
      iv_buf[2] = buf_in[2];
      iv_buf[3] = buf_in[3];
      iv_buf[4] = buf_in[4];
      iv_buf[5] = buf_in[5];
      iv_buf[6] = buf_in[6];
      iv_buf[7] = buf_in[7];
      iv_buf[8] = buf_in[8];
      iv_buf[9] = buf_in[9];
      iv_buf[10] = buf_in[10];
      iv_buf[0xb] = buf_in[0xb];
      iv_buf[0xc] = buf_in[0xc];
      iv_buf[0xd] = buf_in[0xd];
      iv_buf[0xe] = buf_in[0xe];
      iv_buf[0xf] = buf_in[0xf];
    }
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}