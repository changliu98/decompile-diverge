smb_sdrc_t __cdecl smb_com_flush(smb_request_t *sr)
{
  smb_tree *flist; // [rsp+10h] [rbp-20h]
  smb_ofile_t *file; // [rsp+18h] [rbp-18h]

  if ( !smb_flush_required )
    return smbsr_encode_empty_result(sr) != 0;
  if ( sr->smb_fid == 0xFFFF )
  {
    flist = sr->tid_tree;
    smb_llist_enter(&flist->t_ofile_list, RW_READER);
    for ( file = (smb_ofile_t *)smb_llist_head(&flist->t_ofile_list);
          file;
          file = (smb_ofile_t *)smb_llist_next(&flist->t_ofile_list, file) )
    {
      mutex_enter(&file->f_mutex);
      smb_flush_file(sr, file);
      mutex_exit(&file->f_mutex);
    }
    smb_llist_exit(&flist->t_ofile_list);
    return smbsr_encode_empty_result(sr) != 0;
  }
  smbsr_lookup_file(sr);
  if ( sr->fid_ofile )
  {
    smb_flush_file(sr, sr->fid_ofile);
    return smbsr_encode_empty_result(sr) != 0;
  }
  smbsr_status(sr, 0xC0000008, 1u, 6u);
  return 1;
}