static int archive_read_format_rar_read_data(struct archive_read *a,
                                             const void **buff, size_t *size,
                                             int64_t *offset) {
  struct rar *rar = (struct rar *)a->format->data;
  int ret;
  if (rar->entry_bytes_remaining == -1) rar->entry_bytes_remaining = 0;
  if (rar->entry_padding > 0) {
    __archive_read_consume(a, rar->entry_padding);
    rar->entry_padding = 0;
  }
  *buff = NULL;
  if (rar->end_of_entry || rar->entry_uncompressed_remaining >= rar->entry_size) {
    *size = 0;
    *offset = rar->entry_uncompressed_offset;
    if (*offset < rar->entry_size) *offset = rar->entry_size;
    return 1;
  }
  switch (rar->compression_method) {
    case 48:
      return read_data_stored(a, buff, size, offset);
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
      ret = read_data_compressed(a, buff, size, offset);
      if (ret != 0 && ret != (-20)) Ppmd7_Free(&rar->ppmd7);
      return ret;
    default:
      archive_set_error(&a->archive, -1,
                        "Unsupported compression method for RAR file.");
      return (-30);
  }
}