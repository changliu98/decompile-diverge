int blake2b_init(blake2b_state *S,size_t outlen)

{
  blake2b_param P [1];
  size_t outlen_local;
  blake2b_state *S_local;
  int local_c;
  
  if ((outlen == 0) || (0x40 < outlen)) {
    local_c = -1;
  }
  else {
    P[0].digest_length = (uint8_t)outlen;
    P[0].key_length = '\0';
    P[0].fanout = '\x01';
    P[0].depth = '\x01';
    store32(&P[0].leaf_length,0);
    store32(&P[0].node_offset,0);
    store32(&P[0].xof_length,0);
    P[0].node_depth = '\0';
    P[0].inner_length = '\0';
    memset(P[0].reserved,0,0xe);
    memset(P[0].salt,0,0x10);
    memset(P[0].personal,0,0x10);
    local_c = blake2b_init_param(S,P);
  }
  return local_c;
}