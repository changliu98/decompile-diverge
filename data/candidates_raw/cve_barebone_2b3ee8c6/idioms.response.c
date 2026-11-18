static int mac_metadata(struct archive_read *a, struct archive_entry *entry, void *data)
{
  struct zip *zip = (zip *) a->format->data;
  struct zip_entry *ze = (zip_entry *) data;
  long offset = zip_entry_offset(zip->file, 0);
  int ret = 0;
  if (ze->compression != ZIP_COMPRESSION_NONE) {
    __archive_read_warnx(&a->archive, 22,
      "Unsupported ZIP compression method (%s)",
      zip_compression_name(ze->compression));
    return -20;
  }
  if (ze->uncompressed_size > (1024 * 1024 * 4)) {
    __archive_read_warnx(&a->archive, 22,
      "Mac metadata is too large: %jd > 4M bytes",
      ze->uncompressed_size);
    return -20;
  }
  unsigned char *mac = (uint8_t *) xmalloc(ze->uncompressed_size);
  if (mac == ((void *)0)) {
    __archive_read_warnx(&a->archive, 12,
      "Can't allocate memory for Mac metadata");
    return -30;
  }
  if (offset < ze->local_header_offset)
    __archive_read_consume(a, ze->local_header_offset - offset);
  else if (offset != ze->local_header_offset)
    __archive_read_seek(a, ze->local_header_offset, 0);
  long hsize = zip_read_local_header(a, ((void *)0));
  __archive_read_consume(a, hsize);
  unsigned long remaining = ze->compressed_size;
  unsigned long mac_remaining = ze->uncompressed_size;
  unsigned char *mp = mac;
  int eof = 0;
  while (1) {
    unsigned char *data;
    unsigned long size;
    int canread = (eof == 0 && remaining > 0);
    if (!canread)
      break;
    data = __archive_read_ahead(a, 1, &size);
    if (data == ((void *)0)) {
      __archive_read_warnx(&a->archive, 22,
        "Truncated ZIP file header");
      ret = -20;
      goto exit;
    }
    if (size > remaining)
      size = remaining;
    if (ze->compression == ZIP_COMPRESSION_NONE) {
      memcpy(mp, data, size);
      mac_remaining -= size;
      mp += size;
      if (mac_remaining == 0)
        eof = 1;
    }
    __archive_read_consume(a, size);
    remaining -= size;
  }
  archive_entry_set_size(entry, ze->uncompressed_size - mac_remaining);
exit:
  __archive_read_seek(a, offset, 0);
  zip->decompress_init = 0;
  xfree(mac);
  return ret;
}