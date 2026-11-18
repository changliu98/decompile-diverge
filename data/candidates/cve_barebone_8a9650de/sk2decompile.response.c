static u_int store_update(kd_db *db, kdb_incr_update *update) {
  kd_dbx *dbx = db->dbx;
  int n = db->n;
  u_int err;
  XDR xdrs;
  kd_page *page;
  int size;
  size = xdr_sizeof((xdrproc_t)xdr_kdb_incr_update_t, (char *)update);
  if (size + sizeof(*page) > dbx->page_size) {
    err = resize(dbx, n, db->max_n, size + sizeof(*page));
    if (err) return err;
  }
  dbx->locked = 2;
  page = (kd_page *)((char *)dbx + sizeof(*dbx) +
                     (update->page_num - 1) % n * dbx->page_size);
  memset(page, 0, dbx->page_size);
  page->magic = 0x0607080a;
  page->size = size;
  page->page_num = update->page_num;
  page->seq = update->seq;
  page->dirty = 0;
  xdrmem_create(&xdrs, page->data, page->size, XDR_ENCODE);
  if (!xdr_kdb_incr_update_t(&xdrs, update)) return (0xfacafac6);
  page->dirty = 1;
  sync_update(dbx, page);
  dbx->last_page_num = update->page_num;
  dbx->last_seq = update->seq;
  if (dbx->n_updates == 0) {
    dbx->n_updates = 1;
    dbx->first_page_num = update->page_num;
    dbx->first_seq = update->seq;
  } else if (dbx->n_updates < n) {
    dbx->n_updates++;
  } else {
    page = (kd_page *)((char *)dbx + sizeof(*dbx) + (update->page_num % n) * dbx->page_size);
    dbx->first_page_num = page->page_num;
    dbx->first_seq = page->seq;
  }
  dbx->locked = 1;
  sync_header(dbx);
  return 0;
}