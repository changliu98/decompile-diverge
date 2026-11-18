int blake2b_init(blake2b_state *S,size_t outlen)

{
  blake2b_param P;
  size_t outlen_local;
  blake2b_state *S_local;
  int local_c;
  
  if (S == (blake2b_state *)0x0) {
    local_c = -1;
  }
  else if ((outlen == 0) || (0x40 < outlen)) {
    blake2b_invalidate_state(S);
    local_c = -1;
  }
  else {
    P.digest_length = (uint8_t)outlen;
    P.key_length = '\0';
    P.fanout = '\x01';
    P.depth = '\x01';
    P.leaf_length = 0;
    P.node_offset = 0;
    P.node_depth = '\0';
    P.inner_length = '\0';
    memset(P.reserved,0,0xe);
    memset(P.salt,0,0x10);
    memset(P.personal,0,0x10);
    local_c = blake2b_init_param(S,&P);
  }
  return local_c;
}