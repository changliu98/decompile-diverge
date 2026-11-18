int __cdecl mp_dss_print(netdissect_options *ndo, const u_char *opt, u_int opt_len, u_char flags)
{
  uint64_t v4; // rax
  uint32_t v5; // eax
  uint64_t v6; // rax
  uint32_t v7; // eax
  uint32_t v8; // eax
  uint16_t v9; // ax
  uint16_t v10; // ax
  int (*v12)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-A0h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+20h] [rbp-90h]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+30h] [rbp-80h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-68h]
  int (*v16)(netdissect_options *, const char *, ...); // [rsp+58h] [rbp-58h]
  int (*v17)(netdissect_options *, const char *, ...); // [rsp+68h] [rbp-48h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+78h] [rbp-38h]
  const u_char *opta; // [rsp+98h] [rbp-18h]
  const u_char *optb; // [rsp+98h] [rbp-18h]
  const u_char *optd; // [rsp+98h] [rbp-18h]
  const u_char *optc; // [rsp+98h] [rbp-18h]

  if ( opt_len != mp_dss_len((const mp_dss *)opt, 1) && opt_len != mp_dss_len((const mp_dss *)opt, 0)
    || (flags & 2) != 0 )
  {
    return 0;
  }
  if ( (opt[3] & 0x10) != 0 )
    ndo->ndo_printf(ndo, " fin");
  opta = opt + 4;
  if ( (opt[3] & 1) != 0 )
  {
    ndo->ndo_printf(ndo, " ack ");
    if ( (opt[3] & 2) != 0 )
    {
      ndo_printf = ndo->ndo_printf;
      v4 = EXTRACT_64BITS(opta);
      ndo_printf(ndo, "%lu", v4);
      opta = opt + 12;
    }
    else
    {
      v17 = ndo->ndo_printf;
      v5 = EXTRACT_32BITS(opta);
      v17(ndo, "%u", v5);
      opta = opt + 8;
    }
  }
  if ( (opt[3] & 4) != 0 )
  {
    ndo->ndo_printf(ndo, " seq ");
    if ( (opt[3] & 8) != 0 )
    {
      v16 = ndo->ndo_printf;
      v6 = EXTRACT_64BITS(opta);
      v16(ndo, "%lu", v6);
      optb = opta + 8;
    }
    else
    {
      v15 = ndo->ndo_printf;
      v7 = EXTRACT_32BITS(opta);
      v15(ndo, "%u", v7);
      optb = opta + 4;
    }
    v13 = ndo->ndo_printf;
    v8 = EXTRACT_32BITS(optb);
    v13(ndo, " subseq %u", v8);
    optd = optb + 4;
    v14 = ndo->ndo_printf;
    v9 = EXTRACT_16BITS(optd);
    v14(ndo, " len %u", v9);
    optc = optd + 2;
    if ( opt_len == mp_dss_len((const mp_dss *)opt, 1) )
    {
      v12 = ndo->ndo_printf;
      v10 = EXTRACT_16BITS(optc);
      v12(ndo, " csum 0x%x", v10);
    }
  }
  return 1;
}