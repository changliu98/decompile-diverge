unsigned int pktap_if_print(pktap_if_t *pkt, const struct pktap_pkt_info *info,
                            const unsigned char *pkt_data) {
  unsigned int pkt_len = info->pkt_len;
  unsigned int pkt_caplen = info->pkt_caplen;
  unsigned int hdr_len;
  unsigned int link_type;
  const unsigned char *pkt_data_payload;
  u_int32_t link_type_be;
  pktap_printer_t printer;
  if (pkt_len < sizeof(struct pktap_hdr) ||
      pkt_caplen < sizeof(struct pktap_hdr)) {
    pkt->error(pkt, "[|pktap]");
    return 0;
  }
  link_type_be = (pkt_data[8] << 0) | (pkt_data[9] << 8) | (pkt_data[10] << 16) |
                 (pkt_data[11] << 24);
  hdr_len = (pkt_data[0] << 0) | (pkt_data[1] << 8) | (pkt_data[2] << 16) |
            (pkt_data[3] << 24);
  if (hdr_len < sizeof(struct pktap_hdr)) {
    pkt->error(pkt, "[|pktap]");
    return 0;
  }
  if (pkt_len < hdr_len || pkt_caplen < hdr_len) {
    pkt->error(pkt, "[|pktap]");
    return hdr_len;
  }
  if (pkt->header_print) pktap_header_print(pkt, pkt_data, pkt_caplen);
  pkt_caplen -= hdr_len;
  pkt_len -= hdr_len;
  pkt_data_payload = pkt_data + hdr_len;
  link_type = (pkt_data[4] << 0) | (pkt_data[5] << 8) | (pkt_data[6] << 16) |
              (pkt_data[7] << 24);
  if (link_type == 0) {
    pkt->error(pkt, "no data");
    return hdr_len;
  }
  if (link_type != 1) return hdr_len;
  printer = lookup_printer(link_type_be);
  if (printer) {
    hdr_len += printer(pkt, info, pkt_data_payload);
  } else {
    if (!pkt->header_print)
      pktap_header_print(pkt, pkt_data, hdr_len + pkt_caplen);
    if (!pkt->raw_print) pkt->data(pkt, pkt_data_payload, pkt_len);
  }
  return hdr_len;
}