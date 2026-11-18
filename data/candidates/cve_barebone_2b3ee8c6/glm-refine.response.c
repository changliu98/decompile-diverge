int __cdecl zip_read_mac_metadata(archive_read *a, archive_entry *entry, zip_entry *rsrc)
{
  zip *zip;
  int64_t offset;
  ssize_t hsize;
  unsigned __int8 *metadata;
  unsigned __int8 *mp;
  size_t metadata_bytes;
  size_t remaining_bytes;
  int eof;
  int ret;
  ssize_t bytes_avail;
  const unsigned __int8 *p;
  int64_t bytes_used;

  zip = (zip *)a->format->data;
  offset = archive_filter_bytes(&a->archive, 0);
  ret = 0;

  // Reject unsupported compression methods
  if (rsrc->compression)
  {
    archive_set_error(&a->archive, 22, "Unsupported ZIP compression method (%s)", compression_name(rsrc->compression));
    return -20;
  }

  // Reject metadata larger than 4MB
  if (rsrc->uncompressed_size > 0x400000)
  {
    archive_set_error(&a->archive, 22, "Mac metadata is too large: %jd > 4M bytes", rsrc->uncompressed_size);
    return -20;
  }

  // Allocate buffer for uncompressed metadata
  metadata = (unsigned __int8 *)malloc(rsrc->uncompressed_size);
  if (!metadata)
  {
    archive_set_error(&a->archive, 12, "Can't allocate memory for Mac metadata");
    return -30;
  }

  // Seek or consume to the local header offset
  if (offset >= rsrc->local_header_offset)
  {
    if (offset != rsrc->local_header_offset)
      _archive_read_seek(a, rsrc->local_header_offset, 0);
  }
  else
  {
    _archive_read_consume(a, rsrc->local_header_offset - offset);
  }

  // Skip local file header
  hsize = zip_get_local_file_header_size(a, 0LL);
  _archive_read_consume(a, hsize);

  remaining_bytes = rsrc->compressed_size;
  metadata_bytes = rsrc->uncompressed_size;
  mp = metadata;
  eof = 0;

  // Read loop
  while (!eof && remaining_bytes != 0)
  {
    p = (const unsigned __int8 *)_archive_read_ahead(a, 1uLL, &bytes_avail);
    if (!p)
    {
      archive_set_error(&a->archive, 22, "Truncated ZIP file header");
      ret = -20;
      goto exit_mac_metadata;
    }

    if (bytes_avail > remaining_bytes)
      bytes_avail = remaining_bytes;

    // Since we already checked compression == 0, this path is always taken
    if (rsrc->compression)
    {
      bytes_used = 0LL;
    }
    else
    {
      memcpy(mp, p, bytes_avail);
      bytes_used = bytes_avail;
      metadata_bytes -= bytes_avail;
      mp += bytes_avail;
      if (!metadata_bytes)
        eof = 1;
    }

    _archive_read_consume(a, bytes_used);
    remaining_bytes -= bytes_used;
  }

  archive_entry_copy_mac_metadata(entry, metadata, rsrc->uncompressed_size - metadata_bytes);

exit_mac_metadata:
  _archive_read_seek(a, offset, 0);
  zip->decompress_init = 0;
  free(metadata);
  return ret;
}