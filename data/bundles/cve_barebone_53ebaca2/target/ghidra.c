void isakmp_rfc3948_print(netdissect_options *ndo,u_char *bp,u_int length,u_char *bp2)

{
  int iVar1;
  int advance;
  int padlen;
  int enh;
  int nh;
  u_char *bp2_local;
  u_int length_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  bp2_local = bp2;
  length_local = length;
  bp_local = bp;
  ndo_local = ndo;
  if ((length == 1) && (*bp == 0xff)) {
    (*ndo->ndo_printf)(ndo,"isakmp-nat-keep-alive");
  }
  else if (length < 4) {
    (*ndo->ndo_printf)(ndo,"[|isakmp]");
  }
  else if ((((*bp == '\0') && (bp[1] == '\0')) && (bp[2] == '\0')) && (bp[3] == '\0')) {
    (*ndo->ndo_printf)(ndo,"NONESP-encap: ");
    isakmp_print(ndo_local,bp_local + 4,length_local - 4,bp2_local);
  }
  else {
    (*ndo->ndo_printf)(ndo,"UDP-encap: ");
    iVar1 = esp_print(ndo_local,bp_local,length_local,bp2_local,&enh,&padlen);
    if (0 < iVar1) {
      bp_local = bp_local + iVar1;
      length_local = length_local - (iVar1 + padlen);
      nh = enh & 0xff;
      ip_print_inner(ndo_local,bp_local,length_local,nh,bp2_local);
    }
  }
  return;
}