void __cdecl nfs_printfh(netdissect_options *ndo, const uint32_t *dp, const u_int len)
{
  const char *sep; // [rsp+10h] [rbp-90h]
  u_int i; // [rsp+1Ch] [rbp-84h]
  char *spacep; // [rsp+20h] [rbp-80h]
  const char *sfsname; // [rsp+28h] [rbp-78h] BYREF
  uint32_t ino; // [rsp+34h] [rbp-6Ch] BYREF
  my_fsid fsid; // [rsp+38h] [rbp-68h] BYREF
  u_int lena; // [rsp+8Ch] [rbp-14h]
  const uint32_t *dpa; // [rsp+90h] [rbp-10h]
  netdissect_options *ndoa; // [rsp+98h] [rbp-8h]

  ndoa = ndo;
  dpa = dp;
  lena = len;
  sfsname = 0LL;
  if ( ndo->ndo_uflag )
  {
    sep = "";
    ndoa->ndo_printf(ndoa, " fh[");
    for ( i = 0; i < lena; ++i )
    {
      ndoa->ndo_printf(ndoa, "%s%x", sep, dpa[i]);
      sep = ":";
    }
    ndoa->ndo_printf(ndoa, "]");
  }
  else
  {
    Parse_fh((const unsigned __int8 *)dpa, lena, &fsid, &ino, 0LL, &sfsname, 0);
    if ( sfsname )
    {
      strncpy(nfs_printfh_temp, sfsname, 0x40uLL);
      byte_50F0 = 0;
      spacep = strchr(nfs_printfh_temp, 32);
      if ( spacep )
        *spacep = 0;
      ndoa->ndo_printf(ndoa, " fh %s/", nfs_printfh_temp);
    }
    else
    {
      ndoa->ndo_printf(ndoa, " fh %d,%d/", fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor);
    }
    if ( fsid.Fsid_dev.Minor == 257 )
      ndoa->ndo_printf(ndoa, "%s", fsid.Opaque_Handle);
    else
      ndoa->ndo_printf(ndoa, "%ld", ino);
  }
}