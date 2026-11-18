void __cdecl nfs_printfh(netdissect_options *ndo, const uint32_t *dp, const u_int len)
{
  const char *sep;
  u_int i;
  char *spacep;
  const char *sfsname = NULL;
  uint32_t ino;
  my_fsid fsid;

  if (ndo->ndo_uflag)
  {
    // Unformatted handle output mode
    sep = "";
    ndo->ndo_printf(ndo, " fh[");
    for (i = 0; i < len; ++i)
    {
      ndo->ndo_printf(ndo, "%s%x", sep, dp[i]);
      sep = ":";
    }
    ndo->ndo_printf(ndo, "]");
  }
  else
  {
    // Formatted handle output mode
    Parse_fh((const unsigned __int8 *)dp, len, &fsid, &ino, NULL, &sfsname, 0);
    
    if (sfsname)
    {
      // Copy and sanitize the filesystem name
      strncpy(nfs_printfh_temp, sfsname, 0x40uLL);
      byte_50F0 = 0; // Explicit null-termination at the end of the 64-byte buffer
      spacep = strchr(nfs_printfh_temp, ' ');
      if (spacep)
        *spacep = '\0'; // Truncate at the first space
      
      ndo->ndo_printf(ndo, " fh %s/", nfs_printfh_temp);
    }
    else
    {
      // Fallback to printing device major/minor numbers
      ndo->ndo_printf(ndo, " fh %d,%d/", fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor);
    }

    // Print the inode or opaque handle
    if (fsid.Fsid_dev.Minor == 257)
      ndo->ndo_printf(ndo, "%s", fsid.Opaque_Handle);
    else
      ndo->ndo_printf(ndo, "%ld", ino);
  }
}