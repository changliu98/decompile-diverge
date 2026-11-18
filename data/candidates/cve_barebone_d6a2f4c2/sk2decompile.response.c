void nfs_printfh(netdissect_options *ndo, const u_char *fhp,
                 const unsigned int fhsize) {
  unsigned int i;
  const char *sep;
  const char *path = NULL;
  nfsv41_fh4 fh;
  u_long fileid;
  if (ndo->ndo_vflag) {
    sep = "";
    ndo->ndo_printf(ndo, " fh[");
    for (i = 0; i < fhsize; i++) {
      ndo->ndo_printf(ndo, "%s%x", sep, fhp[i]);
      sep = ":";
    }
    ndo->ndo_printf(ndo, "]");
  } else {
    Parse_fh((const unsigned char *)fhp, fhsize, &fh, &fileid, NULL, &path, 0);
    if (path) {
      char *p;
      strncpy(tmpstr, path, 64);
      tmpstr[64 - 1] = '\0';
      p = strchr(tmpstr, ' ');
      if (p) *p = '\0';
      ndo->ndo_printf(ndo, " fh %s/", tmpstr);
    } else {
      ndo->ndo_printf(ndo, " fh %d,%d/", fh.fh_type, fh.fh_fh_type);
    }
    if (fh.fh_fh_type == 257)
      ndo->ndo_printf(ndo, "%s", fh.fh_fh_name);
    else
      ndo->ndo_printf(ndo, "%ld", fileid);
  }
}