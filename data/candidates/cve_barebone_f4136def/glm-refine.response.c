smb_sdrc_t __cdecl smb_com_flush(smb_request_t *sr)
{
  smb_tree_t *tree;
  smb_ofile_t *file;

  // If flushing is globally disabled, return success immediately
  if (!smb_flush_required)
    return smbsr_encode_empty_result(sr) != 0;

  // SMB_FID 0xFFFF indicates a request to flush all open files on the tree
  if (sr->smb_fid == 0xFFFF)
  {
    tree = sr->tid_tree;
    smb_llist_enter(&tree->t_ofile_list, RW_READER);
    
    for (file = (smb_ofile_t *)smb_llist_head(&tree->t_ofile_list);
         file;
         file = (smb_ofile_t *)smb_llist_next(&tree->t_ofile_list, file))
    {
      mutex_enter(&file->f_mutex);
      smb_flush_file(sr, file);
      mutex_exit(&file->f_mutex);
    }
    
    smb_llist_exit(&tree->t_ofile_list);
    return smbsr_encode_empty_result(sr) != 0;
  }

  // Lookup the specific file associated with the FID
  smbsr_lookup_file(sr);
  
  if (sr->fid_ofile)
  {
    smb_flush_file(sr, sr->fid_ofile);
    return smbsr_encode_empty_result(sr) != 0;
  }

  // FID was invalid or file not found: return STATUS_INVALID_HANDLE
  smbsr_status(sr, 0xC0000008, 1u, 6u);
  return 1;
}