static int
smbsr_flush(struct smbsr_request *psr)
{
 int error, ret;
 smb_llist_t *ll;
 smb_ofile_t *of;

 if (!smb_flush_required) {
  error = smbsr_encode_empty_result(psr);
  ret = (error ? 1 : 0);
  goto out;
 }

 if ((psr->req_fid & 0xffff) != 0xffff) {
  smbsr_lookup_file(psr);

  if (psr->psr_of == NULL) {
   smbsr_status(psr, 0xc0000008, 1, 6);
   ret = 1;
   goto out;
  }
  smb_flush_file(psr, psr->psr_of);
 } else {

  ll = psr->psr_ssn->ssn_files;
  smb_llist_enter(ll, 0);
  for (of = smb_llist_head(ll); of != NULL;
      of = smb_llist_next(ll, of)) {
   mutex_enter(&of->o_lock);
   smb_flush_file(psr, of);
   mutex_exit(&of->o_lock);
  }
  smb_llist_exit(ll);
 }

 error = smbsr_encode_empty_result(psr);
 ret = (error ? 1 : 0);

out:
 return (ret);
}