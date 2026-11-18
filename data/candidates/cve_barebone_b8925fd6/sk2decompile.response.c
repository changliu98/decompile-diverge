static int ospf6_print_lshdr(netdissect_options *ndo,
                             const struct lsa6_hdr *lsh, const u_char *maxbuf) {
  if (((const u_char *)(lsh + 1) > maxbuf) ||
      (ndo->ndo_snapend - 2 < (const u_char *)(&lsh->lsa_router)) ||
      (ndo->ndo_snapend - 4 < (const u_char *)(&lsh->lsa_seq)) ||
      (ndo->ndo_snapend - 4 < (const u_char *)(&lsh->lsa_age)))
    return 1;
  ndo->ndo_hexdump(ndo, "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u",
                   ipaddr_string(ndo, &lsh->lsa_router),
                   EXTRACT_32BITS(&lsh->lsa_seq), EXTRACT_16BITS(&lsh->lsa_age),
                   EXTRACT_16BITS(&lsh->ndo_hexdump) - sizeof(*lsh));
  ospf6_print_ls_type(ndo, EXTRACT_16BITS(&lsh->lsa_type), &lsh->lsa_id);
  return 0;
}