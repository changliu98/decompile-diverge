void nfs_printfh(struct netdissect_options *ndo, unsigned int *fh, unsigned int len)
{
  struct my_fsid fsid;
  unsigned int ino;
  char *sfsname = ((void *)0);
  if (ndo->ndo_uflag) {
    char *sep = "";
    unsigned int i;
    ndo->ndo_printf(ndo, " fh[");
    for (i = 0; i < len; i++) {
      ndo->ndo_printf(ndo, "%s%x", sep, ((unsigned int *)fh)[i]);
      sep = ":";
    }
    ndo->ndo_printf(ndo, "]");
  } else {
    nfs_getfsid(fh, len, &fsid, &ino, ((void *)0), &sfsname, ((void *)0));
    if (sfsname != ((void *)0)) {
      char *spacep;
      nfs_printfh_temp[sizeof(nfs_printfh_temp) - 1] = '\0';
      nfs_printfh_temp[sizeof(nfs_printfh_temp) - 1] = '\0';
      spacep = strchr(nfs_printfh_temp, ' ');
      if (spacep != ((void *)0))
        *spacep = '\0';
      ndo->ndo_printf(ndo, " fh %s/", nfs_printfh_temp);
    } else
      ndo->ndo_printf(ndo, " fh %d,%d/",
        fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor);
    if (fsid.Fsid_dev.Minor == 257)
      ndo->ndo_printf(ndo, "%s", fsid.Opaque_Handle);
    else
      ndo->ndo_printf(ndo, "%ld", ino);
  }
}