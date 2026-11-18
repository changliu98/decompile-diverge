static int archive_read_format_rar_read_data(void *data, void **buf, unsigned long *buflen, long *off)
{
  struct archive_read *ar = data;
  struct rar *rar = (rar *)ar->format->data;
  int ret;
  int compression_method;
  if (rar->has_encrypted_entries == -1)
    rar->has_encrypted_entries = 0;
  if (rar->bytes_unconsumed > 0) {
    __archive_read_consume (ar, rar->bytes_unconsumed);
    rar->bytes_unconsumed = 0;
  }
  *buf = ((void *)0);
  if (rar->entry_eof || rar->offset_seek >= rar->unp_size) {
    *buflen = 0;
    *off = rar->offset;
    if (*off < rar->unp_size)
      *off = rar->unp_size;
    return 1;
  }
  compression_method = rar->compression_method;
  switch (compression_method) {
  case 49:
  case 50:
  case 51:
  case 52:
  case 53:
    ret = read_ppmd7(ar, buf, buflen, off);
    if (ret != 0 && ret != -20)
      ppmd7_end(&rar->ppmd7_context);
    break;
  case 48:
    ret = read_raw(ar, buf, buflen, off);
    break;
  default:
    __archive_read_warn (ar->archive, -1,
                         "Unsupported compression method for RAR file.");
    return -30;
  }
  return ret;
}