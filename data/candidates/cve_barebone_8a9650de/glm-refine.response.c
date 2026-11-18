krb5_error_code __cdecl store_update(kdb_log_context *log_ctx, kdb_incr_update_t *upd)
{
  XDR xdrs;
  kdb_hlog_t *ulog;
  uint32_t ulogentries;
  krb5_error_code retval;
  uint32_t upd_size;
  kdb_ent_header_t *indx_log;

  ulog = log_ctx->ulog;
  ulogentries = log_ctx->ulogentries;
  upd_size = xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, upd);

  // Resize the log if the new update doesn't fit in the current block size
  if (upd_size + 28 > ulog->kdb_block)
  {
    retval = resize(ulog, ulogentries, log_ctx->ulogfd, upd_size + 28);
    if (retval)
      return retval;
  }

  ulog->kdb_state = 2; // KDB_UNSTABLE

  // Locate the log entry slot using modulo arithmetic for circular buffer behavior
  indx_log = (kdb_ent_header_t *)((char *)&ulog[1] + ulog->kdb_block * ((upd->kdb_entry_sno - 1) % ulogentries));
  
  memset(indx_log, 0, ulog->kdb_block);
  indx_log->kdb_umagic = 107352594; // Likely a macro like KDB_ULOG_MAGIC
  indx_log->kdb_entry_size = upd_size;
  indx_log->kdb_entry_sno = upd->kdb_entry_sno;
  indx_log->kdb_time = upd->kdb_time;
  indx_log->kdb_commit = 0; // Uncommitted state

  // Serialize the update into the log entry's data buffer
  xdrmem_create(&xdrs, (caddr_t)indx_log->entry_data, indx_log->kdb_entry_size, XDR_ENCODE);
  if (!xdr_kdb_incr_update_t(&xdrs, upd))
    return -1780155650; // Likely KRB5_KDB_LOG_ERR or similar error code

  indx_log->kdb_commit = 1; // Committed state
  sync_update(ulog, indx_log);

  // Update the last sequence number and time in the header
  ulog->kdb_last_sno = upd->kdb_entry_sno;
  ulog->kdb_last_time = upd->kdb_time;

  // Update circular buffer pointers and counts
  if (ulog->kdb_num)
  {
    if (ulog->kdb_num >= ulogentries)
    {
      // Buffer is full, advance the first pointer to the next oldest entry
      uint64_t offset = ulog->kdb_block * (upd->kdb_entry_sno % ulogentries);
      ulog->kdb_first_sno = *(_DWORD *)((char *)&ulog[1].db_version_num + offset);
      ulog->kdb_first_time = *(kdbe_time_t *)((char *)&ulog[1].kdb_num + offset);
    }
    else
    {
      ++ulog->kdb_num;
    }
  }
  else
  {
    // First entry in the log
    ulog->kdb_num = 1;
    ulog->kdb_first_sno = upd->kdb_entry_sno;
    ulog->kdb_first_time = upd->kdb_time;
  }

  ulog->kdb_state = 1; // KDB_STABLE
  sync_header(ulog);

  return 0;
}