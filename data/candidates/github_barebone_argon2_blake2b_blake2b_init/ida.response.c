int __cdecl blake2b_init(blake2b_state *S, size_t outlen)
{
  blake2b_param P; // [rsp+8h] [rbp-58h] BYREF
  size_t outlena; // [rsp+48h] [rbp-18h]
  blake2b_state *Sa; // [rsp+50h] [rbp-10h]

  Sa = S;
  outlena = outlen;
  if ( !S )
    return -1;
  if ( outlena && outlena <= 0x40 )
  {
    P.digest_length = outlena;
    P.key_length = 0;
    P.fanout = 1;
    P.depth = 1;
    P.leaf_length = 0;
    P.node_offset = 0LL;
    P.node_depth = 0;
    P.inner_length = 0;
    memset(P.reserved, 0, sizeof(P.reserved));
    memset(P.salt, 0, sizeof(P.salt));
    memset(P.personal, 0, sizeof(P.personal));
    return blake2b_init_param(Sa, &P);
  }
  else
  {
    blake2b_invalidate_state(Sa);
    return -1;
  }
}