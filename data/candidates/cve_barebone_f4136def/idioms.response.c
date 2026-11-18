int smb_com_flush(struct smb_request *sr)
{
  if (smb_flush_required) {
    if (sr->smb_fid == (0xFFFF)) {
      struct smb_tree *tree = sr->tid_tree;
      struct smb_ofile *file;
      smb_list_lock(&tree->t_ofile_list, RW_READER);
      for (file = smb_list_first(&tree->t_ofile_list);
           file != ((void *)0);
           file = smb_list_next(&tree->t_ofile_list, file)) {
        smb_mutex_lock(&file->f_mutex);
        smb_read_file(sr, file);
        smb_mutex_unlock(&file->f_mutex);
      }
      smb_list_unlock(&tree->t_ofile_list);
    } else {
      smb_read_file(sr);
      if (sr->fid_ofile == ((void *)0)) {
        smb_set_error(sr, (0xC0000008), 1,
                      SMB_RETCODE_NOENT);
        return 1;
      }
    }
  } else {
    if (smb_read_file(sr) == 0)
      return 0;
  }
  return 1;
}