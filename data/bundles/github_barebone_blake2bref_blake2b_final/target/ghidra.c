int blake2b_final(blake2b_state *S,void *out,size_t outlen)

{
  int iVar1;
  size_t i;
  uint8_t buffer [64];
  size_t outlen_local;
  void *out_local;
  blake2b_state *S_local;
  int local_c;
  
  memset(buffer,0,0x40);
  if ((out == (void *)0x0) || (outlen < S->outlen)) {
    local_c = -1;
  }
  else {
    iVar1 = blake2b_is_lastblock(S);
    if (iVar1 == 0) {
      blake2b_increment_counter(S,S->buflen);
      blake2b_set_lastblock(S);
      memset(S->buf + S->buflen,0,0x80 - S->buflen);
      blake2b_compress(S,S->buf);
      for (i = 0; i < 8; i = i + 1) {
        store64(buffer + i * 8,S->h[i]);
      }
      memcpy(out,buffer,S->outlen);
      secure_zero_memory(buffer,0x40);
      local_c = 0;
    }
    else {
      local_c = -1;
    }
  }
  return local_c;
}