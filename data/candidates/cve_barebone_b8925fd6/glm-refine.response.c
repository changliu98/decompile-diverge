int __cdecl ospf6_print_lshdr(netdissect_options *ndo, const lsa6_hdr *lshp, const u_char *dataend)
{
  const char *router_str;
  uint32_t seq;
  uint16_t age;
  uint16_t length;
  uint16_t type;

  // Check if the LSA header fits within bounds and if the specific fields 
  // (ls_type and ls_seq) can be safely accessed without overrunning the snapend.
  if ( &lshp[1] > (const lsa6_hdr *)dataend
    || (const u_char *)&lshp->ls_type > ndo->ndo_snapend - 2
    || (const u_char *)&lshp->ls_seq > ndo->ndo_snapend - 4 )
  {
    return 1;
  }

  router_str = ipaddr_string(ndo, &lshp->ls_router);
  seq = EXTRACT_32BITS(&lshp->ls_seq);
  age = EXTRACT_16BITS(lshp); // ls_age is the first 16-bit field in the header
  length = EXTRACT_16BITS(&lshp->ls_length);
  
  ndo->ndo_printf(
      ndo, 
      "\n\t  Advertising Router %s, seq 0x%08x, age %us, length %u", 
      router_str, 
      seq, 
      age, 
      length - 20
  );

  type = EXTRACT_16BITS(&lshp->ls_type);
  ospf6_print_ls_type(ndo, type, &lshp->ls_stateid);
  
  return 0;
}