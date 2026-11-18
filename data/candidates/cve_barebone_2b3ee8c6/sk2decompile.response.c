static int zip_read_mac_metadata(struct archive_read *a,
                                 struct archive_entry *entry,
                                 struct zip_entry *zip_entry) {
  struct zip *zip = (struct zip *)a->format->data;
  int64_t bytes_skipped = archive_filter_bytes(&a->archive, 0);
  unsigned char *p;
  unsigned char *q;
  int64_t local_header_size;
  int r = 0;
  size_t bytes_read;
  size_t bytes_remaining;
  size_t bytes_to_read;
  int done;
  if (zip_entry->compression_method != 0) {
    archive_set_error(&a->archive, 22,
                      "Unsupported ZIP compression method (%s)",
                      compression_name(zip_entry->compression_method));
    return (-20);
  }
  if (zip_entry->mac_metadata_size > 4194304) {
    archive_set_error(&a->archive, 22,
                      "Mac metadata is too large: %jd > 4M bytes",
                      (intmax_t)zip_entry->mac_metadata_size);
    return (-20);
  }
  p = malloc(zip_entry->mac_metadata_size);
  if (p == NULL) {
    archive_set_error(&a->archive, 12,
                      "Can't allocate memory for Mac metadata");
    return (-30);
  }
  if (bytes_skipped < zip_entry->mac_metadata_offset)
    __archive_read_filter_consume(a, zip_entry->mac_metadata_offset -
                                         bytes_skipped);
  else if (bytes_skipped > zip_entry->mac_metadata_offset)
    __archive_read_filter_skip(a, zip_entry->mac_metadata_offset, 0);
  local_header_size = zip_get_local_file_header_size(a, 0);
  __archive_read_filter_consume(a, local_header_size);
  bytes_remaining = zip_entry->uncompressed_size;
  bytes_to_read = zip_entry->mac_metadata_size;
  q = p;
  done = 0;
  while (!done && bytes_remaining > 0) {
    const void *buff;
    size_t size;
    buff = __archive_read_filter_ahead(a, 1, &size);
    if (buff == NULL) {
      archive_set_error(&a->archive, 22, "Truncated ZIP file header");
      r = (-20);
      goto exit_mac_metadata;
    }
    if (size > bytes_remaining) size = bytes_remaining;
    if (zip_entry->compression_method == 0) {
      memcpy(q, buff, size);
      bytes_read = size;
      bytes_to_read -= bytes_read;
      q += bytes_read;
      if (bytes_to_read == 0) done = 1;
    } else
      bytes_read = 0;
    __archive_read_filter_consume(a, bytes_read);
    bytes_remaining -= bytes_read;
  }
  archive_entry_copy_mac_metadata(entry, p,
                                  zip_entry->mac_metadata_size - bytes_to_read);
exit_mac_metadata:
  __archive_read_filter_skip(a, bytes_skipped, 0);
  zip->entry_compressed_bytes_unread = 0;
  free(p);
  return (r);
}