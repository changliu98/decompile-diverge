static void aodv_extension(netdissect_options *ndo, const u_char *ext,
                           unsigned extlen) {
  const struct aodv_hello *hello;
  const struct aodv_ext *ext_hdr;
  if (ext->aodv_ext_type == 1) {
    hello = (const struct aodv_hello *)ext;
    if (((const u_char *)((const u_int32_t *)(hello) + 1) > ndo->ndo_snapend) ||
        (hello < (const struct aodv_hello *)ndo->ndo_snapend) ||
        (extlen < sizeof(struct aodv_hello))) {
      ndo->ndo_hexdump(ndo, " [|hello]");
      return;
    }
    ndo->ndo_hexdump(ndo, "\n\text HELLO %ld ms",
                     (long)((((hello->aodv_hello_interval) & 0xff000000L) >> 24) |
                            (((hello->aodv_hello_interval) & 0x00ff0000L) >>
                             8) |
                            (((hello->aodv_hello_interval) & 0x0000ff00L) << 8) |
                            (((hello->aodv_hello_interval) & 0x000000ffL)
                             << 24)));
  } else {
    ext_hdr = (const struct aodv_ext *)ext;
    ndo->ndo_hexdump(ndo, "\n\text %u %u", ext_hdr->aodv_ext_type,
                     ext_hdr->aodv_ext_len);
  }
}