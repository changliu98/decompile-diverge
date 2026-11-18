int
store_update(kdb_t *kdb, kdb_incr_update_t *upd)
{
    int ret;
    struct kdb_log *log = kdb->kdb_log;
    unsigned int log_entries = kdb->kdb_log_entries;
    unsigned int recsize, recpos, recend;
    struct kdb_log_entry *le;
    XDR xdrs;

    recsize = sizeof(struct kdb_log_entry) + xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, upd);
    if (recsize > ((unsigned short)(log+1)->l_reclen)) {
        ret = resize(log, log_entries, kdb->kdb_log_fd, recsize);
        if (ret)
            return ret;
    }

    log->l_unsynced = 2;
    recpos = (upd->iu_seqno - 1) % log_entries;
    le = (struct kdb_log_entry *) (((char *)log) + sizeof(struct kdb_log) + recpos * ((unsigned short)(log+1)->l_reclen));
    memset(le, 0, ((unsigned short)(log+1)->l_reclen));
    le->le_magic = 0x06661212;
    le->le_len = recsize;
    le->le_seqno = upd->iu_seqno;
    le->le_prev = upd->iu_prev;
    le->le_next = 0;
    xdrmem_create(&xdrs, (char *) (le + 1), le->le_len, XDR_ENCODE);
    if (!xdr_kdb_incr_update_t(&xdrs, upd)) {
        return (-1812483810L);
    }
    le->le_next = 1;
    sync_update(log, le);

    log->l_last_seqno = upd->iu_seqno;
    log->l_last_prev = upd->iu_prev;
    if (log->l_unsynced == 0) {
        log->l_unsynced = 1;
        log->l_first_seqno = upd->iu_seqno;
        log->l_first_prev = upd->iu_prev;
    } else if (log->l_unsynced < log_entries) {
        log->l_unsynced++;
    } else {
        recpos = (upd->iu_seqno - 1) % log_entries;
        le = (struct kdb_log_entry *) (((char *)log) + sizeof(struct kdb_log) + recpos * ((unsigned short)(log+1)->l_reclen));
        log->l_first_seqno = le->le_seqno;
        log->l_first_prev = le->le_prev;
    }
    log->l_unsynced = 1;
    sync_header(log);

    return 0;
}