int __cdecl ospf6_decode_v3(netdissect_options *ndo, const ospf6hdr *op, const u_char *dataend)
{
  uint32_t v3; // eax
  char *v4; // rax
  const char *v5; // r8
  const char *v6; // rax
  const char *v7; // rax
  const char *v8; // rax
  uint32_t v9; // eax
  char *v10; // rax
  char *v11; // rax
  uint32_t v12; // eax
  const lsa6_hdr *v13; // rsi
  const char *v14; // rax
  uint16_t v15; // ax
  int v16; // eax
  const lsa6_hdr *v17; // rsi
  bool v19; // [rsp+Fh] [rbp-111h]
  int (*v20)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-108h]
  unsigned int v21; // [rsp+34h] [rbp-ECh]
  int (*v22)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-E8h]
  int (*v23)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-D8h]
  int (*v24)(netdissect_options *, const char *, ...); // [rsp+58h] [rbp-C8h]
  int (*v25)(netdissect_options *, const char *, ...); // [rsp+68h] [rbp-B8h]
  int (*v26)(netdissect_options *, const char *, ...); // [rsp+78h] [rbp-A8h]
  int (*v27)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-98h]
  unsigned int v28; // [rsp+98h] [rbp-88h]
  unsigned int v29; // [rsp+9Ch] [rbp-84h]
  int (*v30)(netdissect_options *, const char *, ...); // [rsp+A0h] [rbp-80h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+B0h] [rbp-70h]
  const lsu6 *lsup; // [rsp+C0h] [rbp-60h]
  const dd6 *ddp; // [rsp+C8h] [rbp-58h]
  int i; // [rsp+DCh] [rbp-44h]
  const lsa6 *lsap; // [rsp+E0h] [rbp-40h]
  const lsa6_hdr *lshp; // [rsp+E8h] [rbp-38h]
  const lsa6_hdr *lshpa; // [rsp+E8h] [rbp-38h]
  const lsr6 *lsrp; // [rsp+F0h] [rbp-30h]
  const rtrid_t *ap; // [rsp+F8h] [rbp-28h]

  switch ( op->ospf6_type )
  {
    case 1u:
      ndo_printf = ndo->ndo_printf;
      v3 = EXTRACT_32BITS(&op[1].ospf6_routerid);
      v4 = bittok2str(&ospf6_option_values, "none", v3);
      ndo_printf(ndo, "\n\tOptions [%s]", v4);
      if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)((unsigned __int64)&op[1].ospf6_areaid + 2) > ndo->ndo_snapend - 2 )
        return 1;
      v30 = ndo->ndo_printf;
      v28 = EXTRACT_16BITS(&op[1].ospf6_areaid);
      v29 = EXTRACT_16BITS((char *)&op[1].ospf6_areaid + 2);
      v5 = getname(ndo, &op[1].ospf6_version);
      v30(
        ndo,
        "\n\t  Hello Timer %us, Dead Timer %us, Interface-ID %s, Priority %u",
        v28,
        v29,
        v5,
        LOBYTE(op[1].ospf6_routerid));
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&op[1].ospf6_chksum > ndo->ndo_snapend - 4 )
        return 1;
      if ( EXTRACT_32BITS(&op[1].ospf6_chksum) )
      {
        v27 = ndo->ndo_printf;
        v6 = getname(ndo, (const u_char *)&op[1].ospf6_chksum);
        v27(ndo, "\n\t  Designated Router %s", v6);
      }
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&op[2] > ndo->ndo_snapend - 4 )
        return 1;
      if ( EXTRACT_32BITS(&op[2]) )
      {
        v26 = ndo->ndo_printf;
        v7 = getname(ndo, &op[2].ospf6_version);
        v26(ndo, ", Backup Designated Router %s", v7);
      }
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      ndo->ndo_printf(ndo, "\n\t  Neighbor List:");
      for ( ap = &op[2].ospf6_routerid; ; ++ap )
      {
        if ( ap >= (const rtrid_t *)dataend )
          return 0;
        if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)ap > ndo->ndo_snapend - 4 )
          break;
        v25 = ndo->ndo_printf;
        v8 = getname(ndo, (const u_char *)ap);
        v25(ndo, "\n\t    %s", v8);
      }
      return 1;
    case 2u:
      ddp = (const dd6 *)&op[1];
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)ddp > ndo->ndo_snapend - 4 )
        return 1;
      v24 = ndo->ndo_printf;
      v9 = EXTRACT_32BITS(ddp);
      v10 = bittok2str(&ospf6_option_values, "none", v9);
      v24(ndo, "\n\tOptions [%s]", v10);
      if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)((unsigned __int64)&op[1].ospf6_routerid + 3) > ndo->ndo_snapend - 1 )
        return 1;
      v23 = ndo->ndo_printf;
      v11 = bittok2str(&ospf6_dd_flag_values, "none", HIBYTE(op[1].ospf6_routerid));
      v23(ndo, ", DD Flags [%s]", v11);
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&op[1].ospf6_areaid > ndo->ndo_snapend - 4 )
        return 1;
      v22 = ndo->ndo_printf;
      v21 = EXTRACT_16BITS(&op[1].ospf6_routerid);
      v12 = EXTRACT_32BITS(&op[1].ospf6_areaid);
      v22(ndo, ", MTU %u, DD-Sequence 0x%08x", v21, v12);
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      for ( lshp = (const lsa6_hdr *)&op[1].ospf6_chksum; lshp < (const lsa6_hdr *)dataend; ++lshp )
      {
        v13 = lshp;
        if ( ospf6_print_lshdr(ndo, v13, dataend) )
          return 1;
      }
      return 0;
    case 3u:
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      lsrp = (const lsr6 *)&op[1];
      while ( 2 )
      {
        if ( lsrp >= (const lsr6 *)dataend )
          return 0;
        if ( ndo->ndo_snapend - 12 <= ndo->ndo_snapend && (const u_char *)lsrp <= ndo->ndo_snapend - 12 )
        {
          v20 = ndo->ndo_printf;
          v14 = getname(ndo, (const u_char *)&lsrp->ls_router);
          v20(ndo, "\n\t  Advertising Router %s", v14);
          v15 = EXTRACT_16BITS(&lsrp->ls_type);
          ospf6_print_ls_type(ndo, v15, &lsrp->ls_stateid);
          ++lsrp;
          continue;
        }
        break;
      }
      return 1;
    case 4u:
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      lsup = (const lsu6 *)&op[1];
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)lsup > ndo->ndo_snapend - 4 )
        return 1;
      i = EXTRACT_32BITS(lsup);
      lsap = (const lsa6 *)&op[1].ospf6_routerid;
      while ( 2 )
      {
        v19 = 0;
        if ( lsap < (const lsa6 *)dataend )
        {
          v16 = i--;
          v19 = v16 != 0;
        }
        if ( !v19 )
          return 0;
        if ( !ospf6_print_lsa(ndo, lsap, dataend) )
        {
          lsap = (const lsa6 *)((char *)lsap + EXTRACT_16BITS(&lsap->ls_hdr.ls_length));
          continue;
        }
        break;
      }
      return 1;
    case 5u:
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      lshpa = (const lsa6_hdr *)&op[1];
      break;
    default:
      return 0;
  }
  do
  {
    if ( lshpa >= (const lsa6_hdr *)dataend )
      return 0;
    v17 = lshpa++;
  }
  while ( !ospf6_print_lshdr(ndo, v17, dataend) );
  return 1;
}