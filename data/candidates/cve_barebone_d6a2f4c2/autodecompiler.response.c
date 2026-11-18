static void
nfs_printfh(nfs_client *clp, u_int *fh, int fhsz)
{
 char *fsname = NULL;
 nfs41_fh fhbuf;
 nfs41_fh *fhp = &fhbuf;
 int i;
 char *sep;
 char *sp;

 if (clp->cl_nfs4) {
  sep = "";
  clp->cl_print(clp, " fh[");
  for (i = 0; ; i++) {
   if (i >= fhsz)
    break;
   clp->cl_print(clp, "%s%x", sep, fh[i]);
   sep = ":";
  }
  clp->cl_print(clp, "]");
  return;
 }

 Parse_fh(fh, fhsz, &fhp->fh_len, &fhp->fh_data, NULL, &fsname);

 if (fsname) {
  strncpy(nfs_printfh_temp, fsname, 64);
  nfs_printfh_temp[64 - 1] = '\0';
  sp = strchr(nfs_printfh_temp, ' ');
  if (sp)
   *sp = '\0';
  clp->cl_print(clp, " fh %s/", nfs_printfh_temp);
 } else
  clp->cl_print(clp, " fh %d,%d/", fhp->fh_len, fhp->fh_data);

 if (fhp->fh_len == 257)
  clp->cl_print(clp, "%s", (char *)&fhp->fh_data + 2);
 else
  clp->cl_print(clp, "%ld", fhp->fh_data);
}