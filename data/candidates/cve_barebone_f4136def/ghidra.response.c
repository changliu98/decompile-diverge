smb_sdrc_t smb_com_flush(smb_request_t *sr)

{
  smb_llist_t *ll;
  int iVar1;
  int rc;
  smb_llist_t *flist;
  smb_ofile_t *file;
  smb_request_t *sr_local;
  smb_sdrc_t local_c;
  
  if (smb_flush_required == 0) {
    iVar1 = smbsr_encode_empty_result(sr);
  }
  else {
    if (sr->smb_fid == 0xffff) {
      ll = &sr->tid_tree->t_ofile_list;
      smb_llist_enter(ll,RW_READER);
      for (file = smb_llist_head(ll); file != (smb_ofile_t *)0x0; file = smb_llist_next(ll,file)) {
        mutex_enter(&file->f_mutex);
        smb_flush_file(sr,file);
        mutex_exit(&file->f_mutex);
      }
      smb_llist_exit(ll);
    }
    else {
      smbsr_lookup_file(sr);
      if (sr->fid_ofile == (smb_ofile *)0x0) {
        smbsr_status(sr,0xc0000008,1,6);
        return SDRC_ERROR;
      }
      smb_flush_file(sr,sr->fid_ofile);
    }
    iVar1 = smbsr_encode_empty_result(sr);
  }
  local_c = (smb_sdrc_t)(iVar1 != 0);
  return local_c;
}