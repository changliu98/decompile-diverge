krb5_error_code
store_update(kdb_log_context *log_ctx, kdb_incr_update_t *upd)
{
    kdb_hlog_t *ulog = log_ctx->ulog;
    unsigned ulogentries = log_ctx->ulogentries;
    krb5_error_code ret;
    unsigned recsize;
    kdb_ent_header_t *indx_log;
    unsigned upd_size;
    XDR xdrs;

    upd_size = xdr_sizeof(xdr_kdb_incr_update_t, upd);
    recsize = upd_size + sizeof(kdb_ent_header_t);

    if (recsize > ulog->kdb_block) {
	ret = resize(ulog, ulogentries, log_ctx->ulogfd, recsize);
	if (ret)
	    return ret;
    }

    ulog->kdb_state = 2;

    indx_log = (kdb_ent_header_t *)((char *)&ulog[1] +
				    ((upd->kdb_entry_sno - 1) % ulogentries) *
				    ulog->kdb_block);
    memset(indx_log, 0, ulog->kdb_block);

    indx_log->kdb_umagic = 0x6661212;
    indx_log->kdb_entry_size = upd_size;
    indx_log->kdb_entry_sno = upd->kdb_entry_sno;
    indx_log->kdb_time = upd->kdb_time;
    indx_log->kdb_commit = 0;

    xdrmem_create(&xdrs, (caddr_t)indx_log->entry_data,
		  indx_log->kdb_entry_size, XDR_ENCODE);
    if (!xdr_kdb_incr_update_t(&xdrs, upd))
	return -1746115010;

    indx_log->kdb_commit = 1;
    sync_update(ulog, indx_log);

    ulog->kdb_last_sno = upd->kdb_entry_sno;
    ulog->kdb_last_time = upd->kdb_time;

    if (ulog->kdb_num == 0) {
	ulog->kdb_num = 1;
	ulog->kdb_first_sno = upd->kdb_entry_sno;
	ulog->kdb_first_time = upd->kdb_time;
    } else if (ulog->kdb_num < ulogentries) {
	ulog->kdb_num++;
    } else {
	unsigned i;

	i = (upd->kdb_entry_sno % ulogentries) * ulog->kdb_block;
	ulog->kdb_first_sno = ((kdb_sno_t *)((char *)&ulog[1] + i))[0];
	ulog->kdb_first_time = ((kdbe_time_t *)((char *)&ulog[1] + i))[1];
    }

    ulog->kdb_state = 1;
    sync_header(ulog);

    return 0;
}