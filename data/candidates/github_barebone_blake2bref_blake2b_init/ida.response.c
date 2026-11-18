int __cdecl blake2b_init(blake2b_state *S, size_t outlen)
{
  blake2b_param P[1]; // [rsp+0h] [rbp-60h] BYREF
  size_t outlena; // [rsp+48h] [rbp-18h]
  blake2b_state *Sa; // [rsp+50h] [rbp-10h]

  Sa = S;
  outlena = outlen;
  if ( !outlen || outlena > 0x40 )
    return -1;
  P[0].digest_length = outlena;
  P[0].key_length = 0;
  P[0].fanout = 1;
  P[0].depth = 1;
  store32(&P[0].leaf_length, 0);
  store32(&P[0].node_offset, 0);
  store32(&P[0].xof_length, 0);
  P[0].node_depth = 0;
  P[0].inner_length = 0;
  memset(P[0].reserved, 0, sizeof(P[0].reserved));
  memset(P[0].salt, 0, sizeof(P[0].salt));
  memset(P[0].personal, 0, sizeof(P[0].personal));
  return blake2b_init_param(Sa, P);
}