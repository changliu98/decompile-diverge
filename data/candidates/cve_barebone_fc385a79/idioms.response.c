int gnrc_rpl_srh_process(struct ipv6_hdr *ip, struct gnrc_rpl_srh *rh, void **err_ptr)
{
  struct ipv6_addr_t addr;
  struct gnrc_rpl_srh *rh_next = (gnrc_rpl_srh_t *)((char *)rh + sizeof(gnrc_rpl_srh_t));
  unsigned char seg_left = rh->seg_left - 1;
  if (rh->seg_left > 0)
  {
  }
  else
  {
    do { if (!(rh->seg_left > 0)) { error("rh->seg_left > 0", "/work/harness.c", 165, (char *) __FUNCTION__); return (0); } } while (0);
  }
  unsigned char num_addr = (8 * (rh->len) - (rh->pad_resv & 0xf0) - (16 - (rh->compr & 0xf))) / (16 - (rh->compr & 0xf0)) + 1;
  if (rh->seg_left > (int)num_addr)
  {
    *err_ptr = &rh->seg_left;
    return (0);
  }
  unsigned char current_pos = num_addr - seg_left;
  unsigned char comp_pos = (rh->seg_left == 1) ? (rh->compr & 0xf) : (rh->compr & 0xf0) >> 4;
  unsigned char compri_addr_len = 16 - comp_pos;
  gnrc_rpl_srh_copy(&addr.u8[0], &ip->dst.u8[0], comp_pos);
  gnrc_rpl_srh_copy(&addr.u8[comp_pos], &rh_next[current_pos - 1].addr, 16 - comp_pos);
  if (is_my_addr(&ip->dst))
  {
    return (0);
  }
  if (is_my_addr(&addr))
  {
    return (0);
  }
  if (contains_multiple_of_my_addr(&ip->dst, rh, num_addr, compri_addr_len))
  {
    return (0);
  }
  rh->seg_left = seg_left;
  gnrc_rpl_srh_copy(&rh_next[current_pos - 1].addr, &ip->dst.u8[comp_pos], 16 - comp_pos);
  ip->dst = addr;
  return (2);
}