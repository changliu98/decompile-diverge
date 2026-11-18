void __cdecl arp_print(netdissect_options *ndo, const u_char *bp_0, u_int length, u_int caplen)
{
  const char *v4; // r8
  char *v5; // rax
  const char *v6; // rax
  const char *v7; // rax
  const char *v8; // rax
  const char *v9; // rax
  const char *v10; // rax
  const char *v11; // rax
  const char *v12; // rax
  const char *v13; // rax
  const char *v14; // rax
  const char *v15; // [rsp+10h] [rbp-110h]
  int (*v16)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-108h]
  const char *v17; // [rsp+28h] [rbp-F8h]
  int (*v18)(netdissect_options *, const char *, ...); // [rsp+30h] [rbp-F0h]
  const char *v19; // [rsp+40h] [rbp-E0h]
  int (*v20)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-D8h]
  const char *v21; // [rsp+58h] [rbp-C8h]
  int (*v22)(netdissect_options *, const char *, ...); // [rsp+60h] [rbp-C0h]
  const char *v23; // [rsp+70h] [rbp-B0h]
  int (*v24)(netdissect_options *, const char *, ...); // [rsp+78h] [rbp-A8h]
  int (*v25)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-98h]
  int (*v26)(netdissect_options *, const char *, ...); // [rsp+98h] [rbp-88h]
  int (*v27)(netdissect_options *, const char *, ...); // [rsp+A8h] [rbp-78h]
  const char *v28; // [rsp+B8h] [rbp-68h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+C0h] [rbp-60h]
  const char *v30; // [rsp+D8h] [rbp-48h]
  unsigned int v31; // [rsp+E4h] [rbp-3Ch]
  int (*v32)(netdissect_options *, const char *, ...); // [rsp+E8h] [rbp-38h]
  u_short linkaddr; // [rsp+F8h] [rbp-28h]
  u_short op; // [rsp+FAh] [rbp-26h]
  u_short hrd; // [rsp+FCh] [rbp-24h]
  u_short pro; // [rsp+FEh] [rbp-22h]

  if ( ndo->ndo_snapend - 8 > ndo->ndo_snapend || bp_0 > ndo->ndo_snapend - 8 )
  {
    ndo->ndo_printf(ndo, "%s", "[|ARP]");
    return;
  }
  hrd = EXTRACT_16BITS(bp_0);
  pro = EXTRACT_16BITS(bp_0 + 2);
  op = EXTRACT_16BITS(bp_0 + 6);
  if ( hrd == 15 )
  {
    linkaddr = 1;
  }
  else
  {
    if ( hrd == 19 )
    {
      atmarp_print(ndo, bp_0, length, caplen);
      return;
    }
    linkaddr = 0;
  }
  if ( &ndo->ndo_snapend[-(unsigned __int64)bp_0[5]] <= ndo->ndo_snapend
    && &bp_0[2 * bp_0[4] + 8 + bp_0[5]] <= &ndo->ndo_snapend[-(unsigned __int64)bp_0[5]] )
  {
    if ( !ndo->ndo_eflag )
      ndo->ndo_printf(ndo, "ARP, ");
    if ( (pro == 2048 || pro == 4096) && bp_0[5] == 4 && bp_0[4] && !ndo->ndo_vflag
      || (v32 = ndo->ndo_printf,
          v30 = tok2str(&arphrd_values, "Unknown Hardware (%u)", hrd),
          v31 = bp_0[4],
          v4 = tok2str(&ethertype_values, "Unknown Protocol (0x%04x)", pro),
          v32(ndo, "%s (len %u), %s (len %u)", v30, v31, v4, bp_0[5]),
          ndo->ndo_vflag) )
    {
      ndo_printf = ndo->ndo_printf;
      v5 = (char *)"";
      if ( ndo->ndo_vflag )
        v5 = ", ";
      v28 = v5;
      v6 = tok2str(&arpop_values, "Unknown (%u)", op);
      ndo_printf(ndo, "%s%s ", v28, v6);
      switch ( op )
      {
        case 1u:
          v27 = ndo->ndo_printf;
          v7 = getname(ndo, &bp_0[2 * bp_0[4] + 8 + bp_0[5]]);
          v27(ndo, "who-has %s", v7);
          if ( isnonzero(&bp_0[bp_0[4] + 8 + bp_0[5]], bp_0[4]) )
          {
            v26 = ndo->ndo_printf;
            v8 = linkaddr_string(ndo, &bp_0[bp_0[4] + 8 + bp_0[5]], linkaddr, bp_0[4]);
            v26(ndo, " (%s)", v8);
          }
          v25 = ndo->ndo_printf;
          v9 = getname(ndo, &bp_0[bp_0[4] + 8]);
          v25(ndo, " tell %s", v9);
          goto out;
        case 2u:
          v24 = ndo->ndo_printf;
          v23 = getname(ndo, &bp_0[bp_0[4] + 8]);
          v10 = linkaddr_string(ndo, bp_0 + 8, linkaddr, bp_0[4]);
          v24(ndo, "%s is-at %s", v23, v10);
          goto out;
        case 3u:
          v22 = ndo->ndo_printf;
          v21 = linkaddr_string(ndo, &bp_0[bp_0[4] + 8 + bp_0[5]], linkaddr, bp_0[4]);
          v11 = linkaddr_string(ndo, bp_0 + 8, linkaddr, bp_0[4]);
          v22(ndo, "who-is %s tell %s", v21, v11);
          goto out;
        case 4u:
          v20 = ndo->ndo_printf;
          v19 = linkaddr_string(ndo, &bp_0[bp_0[4] + 8 + bp_0[5]], linkaddr, bp_0[4]);
          v12 = getname(ndo, &bp_0[2 * bp_0[4] + 8 + bp_0[5]]);
          v20(ndo, "%s at %s", v19, v12);
          goto out;
        case 8u:
          v18 = ndo->ndo_printf;
          v17 = linkaddr_string(ndo, &bp_0[bp_0[4] + 8 + bp_0[5]], linkaddr, bp_0[4]);
          v13 = linkaddr_string(ndo, bp_0 + 8, linkaddr, bp_0[4]);
          v18(ndo, "who-is %s tell %s", v17, v13);
          goto out;
        case 9u:
          v16 = ndo->ndo_printf;
          v15 = linkaddr_string(ndo, bp_0 + 8, linkaddr, bp_0[4]);
          v14 = getname(ndo, &bp_0[bp_0[4] + 8]);
          v16(ndo, "%s at %s", v15, v14);
          goto out;
        default:
          ndo->ndo_default_print(ndo, bp_0, caplen);
          break;
      }
    }
    else
    {
out:
      ndo->ndo_printf(ndo, ", length %u", length);
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "%s", "[|ARP]");
    ndo->ndo_default_print(ndo, bp_0, length);
  }
}