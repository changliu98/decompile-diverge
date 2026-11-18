int gnrc_rpl_srh_process(ipv6_hdr_t *ipv6_hdr, gnrc_rpl_srh_t *srh,
                         void **dest) {
  unsigned char *srh_data = (unsigned char *)srh + 1;
  unsigned char new_srh_length = srh->length - 1;
  unsigned char srh_size;
  unsigned char srh_max_length;
  unsigned char srh_data_index;
  unsigned char srh_source_addr_length;
  unsigned char srh_dest_addr_length;
  unsigned char srh_dest_addr_remaining;
  ipv6_addr_t new_source_addr;
  assert(srh->length > 0);
  srh_size = (srh->srh_ver_len * 8) - ((srh->srh_flags_reserved & 0xF0) >> 4) -
             (16 - (srh->srh_next_header & 0x0F));
  srh_max_length = srh_size / (16 - ((srh->srh_next_header & 0xF0) >> 4));
  srh_max_length++;
  if (srh->length > srh_max_length) {
    *dest = &srh->length;
    return 0;
  }
  srh_data_index = srh_max_length - new_srh_length;
  if (srh->length == 1) {
    srh_source_addr_length = srh->srh_next_header & 0x0F;
  } else {
    srh_source_addr_length = (srh->srh_next_header & 0xF0) >> 4;
  }
  srh_dest_addr_length = 16 - srh_source_addr_length;
  srh_dest_addr_remaining = 16 - srh_dest_addr_length;
  memcpy(&new_source_addr, &ipv6_hdr->src, srh_source_addr_length);
  memcpy((unsigned char *)&new_source_addr + srh_source_addr_length,
         srh_data + (srh_data_index - 1) * srh_dest_addr_length,
         srh_dest_addr_remaining);
  if (ipv6_addr_is_multicast(&ipv6_hdr->src)) {
    return 0;
  }
  if (ipv6_addr_is_multicast(&new_source_addr)) {
    return 0;
  }
  *dest = contains_multiple_of_my_addr(&ipv6_hdr->src, srh, srh_max_length,
                                       srh_dest_addr_length);
  if (*dest) {
    return 0;
  }
  srh->length = new_srh_length;
  memcpy(srh_data + (srh_data_index - 1) * srh_dest_addr_length,
         (unsigned char *)&ipv6_hdr->src + srh_source_addr_length,
         srh_dest_addr_remaining);
  ipv6_hdr->src = new_source_addr;
  return 2;
}