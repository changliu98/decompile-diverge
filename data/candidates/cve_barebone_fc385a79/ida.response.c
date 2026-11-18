int __cdecl gnrc_rpl_srh_process(ipv6_hdr_t *ipv6, gnrc_rpl_srh_t *rh, void **err_ptr)
{
  void *v3; // rax
  int v5; // [rsp+4h] [rbp-4Ch]
  uint8_t new_seg_left; // [rsp+Ah] [rbp-46h]
  uint8_t compri_addr_len; // [rsp+Bh] [rbp-45h]
  uint8_t current_pos; // [rsp+Eh] [rbp-42h]
  uint8_t num_addr; // [rsp+Fh] [rbp-41h]
  gnrc_rpl_srh_t *addr_vec; // [rsp+18h] [rbp-38h]
  ipv6_addr_t addr; // [rsp+20h] [rbp-30h] BYREF
  void **err_ptra; // [rsp+30h] [rbp-20h]
  gnrc_rpl_srh_t *rha; // [rsp+38h] [rbp-18h]
  ipv6_hdr_t *ipv6a; // [rsp+40h] [rbp-10h]

  ipv6a = ipv6;
  rha = rh;
  err_ptra = err_ptr;
  addr_vec = rh + 1;
  new_seg_left = rh->seg_left - 1;
  if ( !rh->seg_left )
    __assert_fail(
      "rh->seg_left > 0",
      "/work/harness.c",
      0xA5u,
      "int gnrc_rpl_srh_process(ipv6_hdr_t *, gnrc_rpl_srh_t *, void **)");
  num_addr = (8 * rha->len - ((rha->pad_resv & 0xF0) >> 4) - (16 - (rha->compr & 0xF)))
           / (16 - ((rha->compr & 0xF0) >> 4))
           + 1;
  if ( rha->seg_left <= (int)num_addr )
  {
    current_pos = num_addr - new_seg_left;
    if ( rh->seg_left == 1 )
      LOBYTE(v5) = rha->compr & 0xF;
    else
      v5 = (rha->compr & 0xF0) >> 4;
    compri_addr_len = 16 - ((rha->compr & 0xF0) >> 4);
    memcpy(&addr, &ipv6a->dst, (unsigned __int8)v5);
    memcpy(
      &addr.u8[(unsigned __int8)v5],
      (char *)addr_vec + compri_addr_len * (current_pos - 1),
      (unsigned __int8)(16 - v5));
    if ( ipv6_addr_is_multicast(&ipv6a->dst) )
    {
      return 0;
    }
    else if ( ipv6_addr_is_multicast(&addr) )
    {
      return 0;
    }
    else
    {
      v3 = contains_multiple_of_my_addr(&ipv6a->dst, rha, num_addr, compri_addr_len);
      *err_ptra = v3;
      if ( v3 )
      {
        return 0;
      }
      else
      {
        rha->seg_left = new_seg_left;
        memcpy(
          (char *)addr_vec + compri_addr_len * (current_pos - 1),
          &ipv6a->dst.u8[(unsigned __int8)v5],
          (unsigned __int8)(16 - v5));
        ipv6a->dst = addr;
        return 2;
      }
    }
  }
  else
  {
    *err_ptra = &rha->seg_left;
    return 0;
  }
}