static int
zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
    struct zip *zip)
{
 struct zip_entry *e = a->format->data;
 int64_t remaining_bytes, metadata_bytes, local_header_offset;
 unsigned long remaining, consumed;
 unsigned char *p, *mp, *metadata;
 size_t hsize;
 int ret, eof;
 ssize_t bytes_avail;

 local_header_offset = archive_filter_bytes(&a->filter[0]);
 ret = 0;

 if (zip->mac_metadata.method == 0)
  goto skip;

 if (zip->mac_metadata.method != 8) {
  archive_set_error(&a->archive, 22,
      "Unsupported ZIP compression method (%s)",
      compression_name(zip->mac_metadata.method));
  return (-20);
 }

 if (zip->mac_metadata.uncompressed_size > 4*1024*1024) {
  archive_set_error(&a->archive, 22,
      "Mac metadata is too large: %jd > 4M bytes",
      (intmax_t)zip->mac_metadata.uncompressed_size);
  return (-20);
 }

 metadata = malloc((size_t)zip->mac_metadata.uncompressed_size);
 if (metadata == NULL) {
  archive_set_error(&a->archive, 12,
      "Can't allocate memory for Mac metadata");
  return (-30);
 }

 if (local_header_offset < zip->mac_metadata.offset)
  __archive_read_consume(a, zip->mac_metadata.offset - local_header_offset);
 else if (local_header_offset != zip->mac_metadata.offset)
  __archive_read_seek(a, zip->mac_metadata.offset, 0);

 hsize = zip_get_local_file_header_size(a, NULL);
 __archive_read_consume(a, hsize);

 remaining_bytes = zip->mac_metadata.compressed_size;
 metadata_bytes = zip->mac_metadata.uncompressed_size;
 mp = metadata;
 eof = 0;

 while ((eof == 0) && (remaining_bytes != 0)) {
  if ((remaining = (unsigned long)remaining_bytes) > remaining_bytes)
   remaining = (unsigned long)remaining_bytes;
  if (zip->mac_metadata.method == 0) {
   while (remaining != 0) {
    p = __archive_read_ahead(a, 1, &bytes_avail);
    if (p == NULL) {
     archive_set_error(&a->archive, 22,
         "Truncated ZIP file header");
     ret = (-20);
     goto exit_mac_metadata;
    }
    if ((size_t)bytes_avail > remaining)
     bytes_avail = remaining;
    memcpy(mp, p, bytes_avail);
    consumed = bytes_avail;
    metadata_bytes -= consumed;
    mp += consumed;
    if (metadata_bytes == 0)
     eof = 1;
   }
  } else {
   consumed = 0;
  }
  __archive_read_consume(a, consumed);
  remaining_bytes -= consumed;
 }

 archive_entry_copy_mac_metadata(entry, metadata,
     (size_t)zip->mac_metadata.uncompressed_size - metadata_bytes);

exit_mac_metadata:

 __archive_read_seek(a, local_header_offset, 0);
 e->end_of_entry = 0;
 free(metadata);
 return (ret);
skip:
 return (0);
}