void nfs_printfh(netdissect_options *ndo,uint32_t *dp,u_int len)

{
  char *pcVar1;
  char *sep;
  u_int i;
  char *spacep;
  char *sfsname;
  uint32_t ino;
  my_fsid fsid;
  u_int len_local;
  uint32_t *dp_local;
  netdissect_options *ndo_local;
  
  sfsname = (char *)0x0;
  if (ndo->ndo_uflag == 0) {
    Parse_fh((uchar *)dp,len,&fsid,&ino,(char **)0x0,&sfsname,0);
    if (sfsname == (char *)0x0) {
      (*ndo->ndo_printf)(ndo," fh %d,%d/",(ulong)fsid.Fsid_dev.Major,(ulong)fsid.Fsid_dev.Minor);
    }
    else {
      strncpy(nfs_printfh::temp,sfsname,0x40);
      nfs_printfh::temp[0x40] = '\0';
      pcVar1 = strchr(nfs_printfh::temp,0x20);
      if (pcVar1 != (char *)0x0) {
        *pcVar1 = '\0';
      }
      (*ndo->ndo_printf)(ndo," fh %s/",nfs_printfh::temp);
    }
    if (fsid.Fsid_dev.Minor == 0x101) {
      (*ndo->ndo_printf)(ndo,"%s",fsid.Opaque_Handle);
    }
    else {
      (*ndo->ndo_printf)(ndo,"%ld",(ulong)ino);
    }
  }
  else {
    sep = "";
    (*ndo->ndo_printf)(ndo," fh[");
    for (i = 0; i < len; i = i + 1) {
      (*ndo->ndo_printf)(ndo,"%s%x",sep,(ulong)dp[i]);
      sep = ":";
    }
    (*ndo->ndo_printf)(ndo,"]");
  }
  return;
}