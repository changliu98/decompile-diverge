int store_update(struct kdb_log_context *ctx, struct kdb_incr_update *upd)
{
    struct kdb_log *log = ctx->ulog;
    struct kdb_ent_header *logent;
    struct xdr_stream xdrstream;
    unsigned int logentsize;
    unsigned int logentno;
    int ret;
    logentno = (upd->kdb_entry_sno - 1) % ctx->ulogentries;
    logentsize = kdb_log_calc_size((int (*)(struct xdr *, void *, unsigned int, int))xdr_kdb_incr_update, upd);
    if (logentsize + sizeof(struct kdb_ent_header) > log->kdb_block) {
        ret = kdb_log_resize(log, ctx->ulogentries, ctx->ulogfd,
                             logentsize + sizeof(struct kdb_ent_header));
        if (ret != (0))
            return (ret);
    }
    log->kdb_state = (1);
    logent = (struct kdb_ent_header *)((char *)log +
                                      log->kdb_block * logentno);
    kdb_log_read(logent, 0, log->kdb_block);
    logent->kdb_umagic = (0x4000000 + 1000000 + 1000 + 4);
    logent->kdb_entry_size = logentsize;
    logent->kdb_entry_sno = upd->kdb_entry_sno;
    logent->kdb_time = upd->kdb_time;
    logent->kdb_commit = (0);
    xdrstream.x_op = xdr_op::XDR_ENCODE;
    xdrstream.x_public = &logent->entry_data;
    xdrstream.x_private = (char *)logent->entry_data;
    xdrstream.x_handy = logent->kdb_entry_size;
    xdr_kdb_ent_header(&xdrstream, logent);
    if (!xdr_kdb_incr_update(&xdrstream, upd))
        return ((-10000000 - 15000000 - 1000 - 1));
    logent->kdb_commit = (1);
    kdb_log_write(log, logent);
    log->kdb_last_sno = upd->kdb_entry_sno;
    log->kdb_last_time = upd->kdb_time;
    if (log->kdb_num == 0) {
        log->kdb_num = 1;
        log->kdb_first_sno = upd->kdb_entry_sno;
        log->kdb_first_time = upd->kdb_time;
    } else if (log->kdb_num < ctx->ulogentries) {
        log->kdb_num++;
    } else {
        logent = (struct kdb_ent_header *)((char *)log +
                                          log->kdb_block *
                                          (upd->kdb_entry_sno %
                                           ctx->ulogentries));
        log->kdb_first_sno = logent->kdb_entry_sno;
        log->kdb_first_time = logent->kdb_time;
    }
    log->kdb_state = (2);
    kdb_log_sync(log);
    return (0);
}