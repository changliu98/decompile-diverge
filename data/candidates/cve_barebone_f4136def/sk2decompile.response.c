static int smb_com_flush(struct smb_request *req) {
  if (!smb_flush_enabled) {
    if (smbsr_encode_empty_result(req)) return 1;
    return 0;
  }
  if (req->tid == 0xffff) {
    SMBSRV_CONNINFO *conn = req->sr;
    SMBSR_FILE *file;
    smb_llist_enter(&conn->sr_files, smb_llist_lock);
    for (file = smb_llist_head(&conn->sr_files); file;
         file = smb_llist_next(&conn->sr_files, file)) {
      mutex_enter(&file->sr_lock);
      smb_flush_file(req, file);
      mutex_exit(&file->sr_lock);
    }
    smb_llist_exit(&conn->sr_files);
  } else {
    smbsr_lookup_file(req);
    if (req->sr_file == NULL) {
      smbsr_status(req, 0xc0000028, 1, 6);
      return 1;
    }
    smb_flush_file(req, req->sr_file);
  }
  if (smbsr_encode_empty_result(req)) return 1;
  return 0;
}