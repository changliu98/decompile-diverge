krb5_error_code store_update(kdb_log_context *log_ctx,kdb_incr_update_t *upd)

{
  uint ulogentries_00;
  kdb_hlog_t *ulog_00;
  uint recsize_00;
  bool_t bVar1;
  unsigned_long uVar2;
  kdb_ent_header_t *upd_00;
  ulong uVar3;
  uint32_t ulogentries;
  kdb_hlog_t *ulog;
  krb5_error_code retval;
  unsigned_long upd_size;
  uint recsize;
  uint i;
  kdb_ent_header_t *indx_log;
  XDR xdrs;
  kdb_incr_update_t *upd_local;
  kdb_log_context *log_ctx_local;
  krb5_error_code local_c;
  
  ulog_00 = log_ctx->ulog;
  ulogentries_00 = log_ctx->ulogentries;
  uVar2 = xdr_sizeof(xdr_kdb_incr_update_t,upd);
  recsize_00 = (uint32_t)uVar2 + 0x1c;
  if ((recsize_00 <= ulog_00->kdb_block) ||
     (local_c = resize(ulog_00,ulogentries_00,log_ctx->ulogfd,recsize_00), local_c == 0)) {
    ulog_00->kdb_state = 2;
    upd_00 = (kdb_ent_header_t *)
             ((long)&ulog_00[1].kdb_hmagic +
             (ulong)(((upd->kdb_entry_sno - 1) % ulogentries_00) * (uint)ulog_00->kdb_block));
    memset(upd_00,0,(ulong)ulog_00->kdb_block);
    upd_00->kdb_umagic = 0x6661212;
    upd_00->kdb_entry_size = (uint32_t)uVar2;
    upd_00->kdb_entry_sno = upd->kdb_entry_sno;
    upd_00->kdb_time = upd->kdb_time;
    upd_00->kdb_commit = 0;
    xdrmem_create(&xdrs,(caddr_t)upd_00->entry_data,upd_00->kdb_entry_size,XDR_ENCODE);
    bVar1 = xdr_kdb_incr_update_t(&xdrs,upd);
    if (bVar1 == 0) {
      local_c = -0x6a1b0502;
    }
    else {
      upd_00->kdb_commit = 1;
      sync_update(ulog_00,upd_00);
      ulog_00->kdb_last_sno = upd->kdb_entry_sno;
      ulog_00->kdb_last_time = upd->kdb_time;
      if (ulog_00->kdb_num == 0) {
        ulog_00->kdb_num = 1;
        ulog_00->kdb_first_sno = upd->kdb_entry_sno;
        ulog_00->kdb_first_time = upd->kdb_time;
      }
      else if (ulog_00->kdb_num < ulogentries_00) {
        ulog_00->kdb_num = ulog_00->kdb_num + 1;
      }
      else {
        uVar3 = (ulong)((upd->kdb_entry_sno % ulogentries_00) * (uint)ulog_00->kdb_block);
        ulog_00->kdb_first_sno = *(kdb_sno_t *)((long)&ulog_00[1].db_version_num + uVar3);
        ulog_00->kdb_first_time = *(kdbe_time_t *)((long)&ulog_00[1].kdb_num + uVar3);
      }
      ulog_00->kdb_state = 1;
      sync_header(ulog_00);
      local_c = 0;
    }
  }
  return local_c;
}