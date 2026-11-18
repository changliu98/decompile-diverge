int __cdecl lldp_mgmt_addr_tlv_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{
  const char *v3; // rax
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-40h]
  const char *mgmt_addr; // [rsp+18h] [rbp-38h]
  u_int tlen; // [rsp+24h] [rbp-2Ch]
  u_int tlena; // [rsp+24h] [rbp-2Ch]
  u_int tlenb; // [rsp+24h] [rbp-2Ch]
  const u_char *tptr; // [rsp+28h] [rbp-28h]
  const u_char *tptra; // [rsp+28h] [rbp-28h]
  const u_char *tptrb; // [rsp+28h] [rbp-28h]
  uint8_t oid_len; // [rsp+31h] [rbp-1Fh]
  uint8_t intf_num_subtype; // [rsp+32h] [rbp-1Eh]
  uint8_t mgmt_addr_len; // [rsp+33h] [rbp-1Dh]

  if ( !len )
    return 0;
  tptr = pptr + 1;
  mgmt_addr_len = *pptr;
  tlen = len - 1;
  if ( len - 1 < *pptr )
    return 0;
  mgmt_addr = lldp_network_addr_print(ndo, tptr, mgmt_addr_len);
  if ( !mgmt_addr )
    return 0;
  ndo->ndo_printf(ndo, "\n\t  Management Address length %u, %s", mgmt_addr_len, mgmt_addr);
  tptra = &tptr[mgmt_addr_len];
  tlena = tlen - mgmt_addr_len;
  if ( tlena >= 5 )
  {
    intf_num_subtype = *tptra;
    ndo_printf = ndo->ndo_printf;
    v3 = tok2str(&lldp_intf_numb_subtype_values, "Unknown", *tptra);
    ndo_printf(
      ndo,
      "\n\t  %s Interface Numbering (%u): %u",
      v3,
      intf_num_subtype,
      _byteswap_ulong(*(_DWORD *)(tptra + 1)));
    tptrb = tptra + 5;
    tlenb = tlena - 5;
    if ( tlenb )
    {
      oid_len = *tptrb;
      if ( tlenb < *tptrb )
        return 0;
      if ( oid_len )
      {
        ndo->ndo_printf(ndo, "\n\t  OID length %u", oid_len);
        safeputs(ndo, tptrb + 1, oid_len);
      }
    }
    return 1;
  }
  return 0;
}