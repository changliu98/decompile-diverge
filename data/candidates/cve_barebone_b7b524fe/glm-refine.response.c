int __cdecl ospf6_decode_v3(netdissect_options *ndo, const ospf6hdr *op, const u_char *dataend)
{
  uint32_t v3; 
  const char *v4; 
  const char *v5; 
  const char *v6; 
  const char *v7; 
  const char *v8; 
  uint32_t v9; 
  const char *v10; 
  const char *v11; 
  uint32_t v12; 
  uint16_t v15; 
  const lsa6_hdr *v17; 
  bool v19; 
  unsigned int v21; 
  unsigned int v28; 
  unsigned int v29; 
  const lsu6 *lsup; 
  const dd6 *ddp; 
  int i; 
  const lsa6 *lsap; 
  const lsa6_hdr *lshp; 
  const lsa6_hdr *lshpa; 
  const lsr6 *lsrp; 
  const rtrid_t *ap; 

  switch ( op->ospf6_type )
  {
    case 1u:
      v3 = EXTRACT_32BITS(&op[1].ospf6_routerid);
      v4 = bittok2str(&ospf6_option_values, "none", v3);
      ndo->ndo_printf(ndo, "\n\tOptions [%s]", v4);
      if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)((unsigned __int64)&op[1].ospf6_areaid + 2) > ndo->ndo_snapend - 2 )
        return 1;
      v28 = EXTRACT_16BITS(&op[1].ospf6_areaid);
      v29 = EXTRACT_16BITS((char *)&op[1].ospf6_areaid + 2);
      v5 = getname(ndo, &op[1].ospf6_version);
      ndo->ndo_printf(
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
        v6 = getname(ndo, (const u_char *)&op[1].ospf6_chksum);
        ndo->ndo_printf(ndo, "\n\t  Designated Router %s", v6);
      }
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&op[2] > ndo->ndo_snapend - 4 )
        return 1;
      if ( EXTRACT_32BITS(&op[2]) )
      {
        v7 = getname(ndo, &op[2].ospf6_version);
        ndo->ndo_printf(ndo, ", Backup Designated Router %s", v7);
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
        v8 = getname(ndo, (const u_char *)ap);
        ndo->ndo_printf(ndo, "\n\t    %s", v8);
      }
      return 1;

    case 2u:
      ddp = (const dd6 *)&op[1];
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)ddp > ndo->ndo_snapend - 4 )
        return 1;
      v9 = EXTRACT_32BITS(ddp);
      v10 = bittok2str(&ospf6_option_values, "none", v9);
      ndo->ndo_printf(ndo, "\n\tOptions [%s]", v10);
      if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend )
        return 1;
      if ( (const u_char *)((unsigned __int64)&op[1].ospf6_routerid + 3) > ndo->ndo_snapend - 1 )
        return 1;
      v11 = bittok2str(&ospf6_dd_flag_values, "none", HIBYTE(op[1].ospf6_routerid));
      ndo->ndo_printf(ndo, ", DD Flags [%s]", v11);
      if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || (const u_char *)&op[1].ospf6_areaid > ndo->ndo_snapend - 4 )
        return 1;
      v21 = EXTRACT_16BITS(&op[1].ospf6_routerid);
      v12 = EXTRACT_32BITS(&op[1].ospf6_areaid);
      ndo->ndo_printf(ndo, ", MTU %u, DD-Sequence 0x%08x", v21, v12);
      if ( ndo->ndo_vflag <= 1 )
        return 0;
      for ( lshp = (const lsa6_hdr *)&op[1].ospf6_chksum; lshp < (const lsa6_hdr *)dataend; ++lshp )
      {
        if ( ospf6_print_lshdr(ndo, lshp, dataend) )
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
          v14 = getname(ndo, (const u_char *)&lsrp->ls_router);
          ndo->ndo_printf(ndo, "\n\t  Advertising Router %s", v14);
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