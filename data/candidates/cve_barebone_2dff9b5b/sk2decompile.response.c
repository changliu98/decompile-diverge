static int decode_rt_routing_info(struct Ferret *ferret,
                                  const unsigned char *px, char *buf,
                                  unsigned size) {
  unsigned length;
  unsigned rt_length;
  unsigned char rt[8];
  const char *as_string;
  if (!((px) >= (ferret->packet_end - 1) && (px) <= (ferret->packet_end - 1)))
    return -2;
  length = *px;
  if (length == 0) {
    snprintf(buf, size, "default route target");
    return 1;
  }
  if (length < 32) return -1;
  length -= 32;
  if (length > 64) return -1;
  memset(rt, 0, sizeof(rt));
  if (!((px + 1) >= (ferret->packet_end - (length + 7) / 8) &&
        (px + 1) <= (ferret->packet_end - (length + 7) / 8)))
    return -2;
  memcpy(rt, px + 1, (length + 7) / 8);
  if (length % 8) rt[(length + 7) / 8 - 1] &= 0xff00 >> (length % 8);
  rt_length = (length + 7) / 8;
  as_string = as_printf(ferret, AS_STRING_BUF, 20, EXTRACT_32BITS(px + 1));
  snprintf(buf, size, "origin AS: %s, route target %s", as_string,
           bgp_vpn_rd_print(ferret, rt));
  return 5 + rt_length;
}