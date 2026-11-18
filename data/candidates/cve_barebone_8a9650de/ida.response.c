krb5_error_code __cdecl store_update(kdb_log_context *log_ctx, kdb_incr_update_t *upd)
{
  __int64 v2; // rcx
  uint32_t ulogentries; // [rsp+Ch] [rbp-74h]
  kdb_hlog_t *ulog; // [rsp+10h] [rbp-70h]
  krb5_error_code retval; // [rsp+1Ch] [rbp-64h]
  uint32_t upd_size; // [rsp+20h] [rbp-60h]
  kdb_ent_header_t *indx_log; // [rsp+30h] [rbp-50h]
  XDR xdrs; // [rsp+38h] [rbp-48h] BYREF
  kdb_incr_update_t *upda; // [rsp+68h] [rbp-18h]
  kdb_log_context *log_ctxa; // [rsp+70h] [rbp-10h]

  log_ctxa = log_ctx;
  upda = upd;
  ulog = log_ctx->ulog;
  ulogentries = log_ctx->ulogentries;
  upd_size = xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, upd);
  if ( upd_size + 28 > ulog->kdb_block )
  {
    retval = resize(ulog, ulogentries, log_ctxa->ulogfd, upd_size + 28);
    if ( retval )
      return retval;
  }
  ulog->kdb_state = 2;
  indx_log = (kdb_ent_header_t *)((char *)&ulog[1] + ulog->kdb_block * ((upda->kdb_entry_sno - 1) % ulogentries));
  memset(indx_log, 0, ulog->kdb_block);
  indx_log->kdb_umagic = 107352594;
  indx_log->kdb_entry_size = upd_size;
  indx_log->kdb_entry_sno = upda->kdb_entry_sno;
  indx_log->kdb_time = upda->kdb_time;
  indx_log->kdb_commit = 0;
  xdrmem_create(&xdrs, (caddr_t)indx_log->entry_data, indx_log->kdb_entry_size, xdr_op::XDR_ENCODE);
  if ( !xdr_kdb_incr_update_t(&xdrs, upda) )
    return -1780155650;
  indx_log->kdb_commit = 1;
  sync_update(ulog, indx_log);
  ulog->kdb_last_sno = upda->kdb_entry_sno;
  ulog->kdb_last_time = upda->kdb_time;
  if ( ulog->kdb_num )
  {
    if ( ulog->kdb_num >= ulogentries )
    {
      v2 = ulog->kdb_block * (upda->kdb_entry_sno % ulogentries);
      ulog->kdb_first_sno = *(_DWORD *)((char *)&ulog[1].db_version_num + v2);
      ulog->kdb_first_time = *(kdbe_time_t *)((char *)&ulog[1].kdb_num + v2);
    }
    else
    {
      ++ulog->kdb_num;
    }
  }
  else
  {
    ulog->kdb_num = 1;
    ulog->kdb_first_sno = upda->kdb_entry_sno;
    ulog->kdb_first_time = upda->kdb_time;
  }
  ulog->kdb_state = 1;
  sync_header(ulog);
  return 0;
}