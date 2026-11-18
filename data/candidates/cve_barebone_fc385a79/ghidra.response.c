int gnrc_rpl_srh_process(ipv6_hdr_t *ipv6,gnrc_rpl_srh_t *rh,void **err_ptr)

{
  uint8_t uVar1;
  byte bVar2;
  byte bVar3;
  _Bool _Var4;
  void *pvVar5;
  byte local_54;
  uint8_t new_seg_left;
  uint8_t compri_addr_len;
  uint8_t addr_len;
  uint8_t pref_elided;
  uint8_t current_pos;
  uint8_t num_addr;
  uint8_t *current_address;
  uint8_t *addr_vec;
  ipv6_addr_t addr;
  void **err_ptr_local;
  gnrc_rpl_srh_t *rh_local;
  ipv6_hdr_t *ipv6_local;
  int local_c;
  
  uVar1 = rh->seg_left + 0xff;
  err_ptr_local = err_ptr;
  rh_local = rh;
  ipv6_local = ipv6;
  if (rh->seg_left != '\0') {
    bVar2 = (char)((int)(((uint)rh->len * 8 - ((int)(rh->pad_resv & 0xf0) >> 4)) -
                        (0x10 - (rh->compr & 0xf))) / (0x10 - ((int)(rh->compr & 0xf0) >> 4))) + 1;
    if (bVar2 < rh->seg_left) {
      *err_ptr = &rh->seg_left;
      local_c = 0;
    }
    else {
      if (uVar1 == '\0') {
        local_54 = rh->compr & 0xf;
      }
      else {
        local_54 = (byte)((int)(rh->compr & 0xf0) >> 4);
      }
      bVar3 = 0x10 - (char)((int)(rh->compr & 0xf0) >> 4);
      memcpy(&addr,&ipv6->dst,(ulong)local_54);
      memcpy((void *)((long)&addr + (ulong)local_54),
             &rh[1].nh + (int)(((byte)(bVar2 - uVar1) - 1) * (uint)bVar3),
             (ulong)(byte)(0x10 - local_54));
      _Var4 = ipv6_addr_is_multicast(&ipv6_local->dst);
      if (_Var4) {
        local_c = 0;
      }
      else {
        _Var4 = ipv6_addr_is_multicast(&addr);
        if (_Var4) {
          local_c = 0;
        }
        else {
          pvVar5 = _contains_multiple_of_my_addr(&ipv6_local->dst,rh_local,(uint)bVar2,(uint)bVar3);
          *err_ptr_local = pvVar5;
          if (pvVar5 == (void *)0x0) {
            rh_local->seg_left = uVar1;
            memcpy(&rh[1].nh + (int)(((byte)(bVar2 - uVar1) - 1) * (uint)bVar3),
                   (void *)((long)&ipv6_local->dst + (ulong)local_54),(ulong)(byte)(0x10 - local_54)
                  );
            (ipv6_local->dst).u64[0] = addr.u64[0];
            (ipv6_local->dst).u64[1] = addr.u64[1];
            local_c = 2;
          }
          else {
            local_c = 0;
          }
        }
      }
    }
    return local_c;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("rh->seg_left > 0","/work/harness.c",0xa5,
                "int gnrc_rpl_srh_process(ipv6_hdr_t *, gnrc_rpl_srh_t *, void **)");
}