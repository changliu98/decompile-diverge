int __cdecl zip_read_mac_metadata(archive_read *a, archive_entry *entry, zip_entry *rsrc)
{
  const char *v3; // rax
  bool v5; // [rsp+Fh] [rbp-81h]
  int64_t bytes_used; // [rsp+18h] [rbp-78h]
  ssize_t bytes_avail; // [rsp+20h] [rbp-70h] BYREF
  const unsigned __int8 *p; // [rsp+28h] [rbp-68h]
  int eof; // [rsp+30h] [rbp-60h]
  int ret; // [rsp+34h] [rbp-5Ch]
  ssize_t hsize; // [rsp+38h] [rbp-58h]
  size_t metadata_bytes; // [rsp+40h] [rbp-50h]
  size_t remaining_bytes; // [rsp+48h] [rbp-48h]
  int64_t offset; // [rsp+50h] [rbp-40h]
  unsigned __int8 *mp; // [rsp+58h] [rbp-38h]
  unsigned __int8 *metadata; // [rsp+60h] [rbp-30h]
  zip *zip; // [rsp+68h] [rbp-28h]
  zip_entry *rsrca; // [rsp+70h] [rbp-20h]
  archive_entry *entrya; // [rsp+78h] [rbp-18h]
  archive_read *aa; // [rsp+80h] [rbp-10h]

  aa = a;
  entrya = entry;
  rsrca = rsrc;
  zip = (zip *)a->format->data;
  offset = archive_filter_bytes(&a->archive, 0);
  ret = 0;
  if ( rsrca->compression )
  {
    v3 = compression_name(rsrca->compression);
    archive_set_error(&aa->archive, 22, "Unsupported ZIP compression method (%s)", v3);
    return -20;
  }
  else if ( rsrca->uncompressed_size <= 0x400000 )
  {
    metadata = (unsigned __int8 *)malloc(rsrca->uncompressed_size);
    if ( metadata )
    {
      if ( offset >= rsrca->local_header_offset )
      {
        if ( offset != rsrca->local_header_offset )
          _archive_read_seek(aa, rsrca->local_header_offset, 0);
      }
      else
      {
        _archive_read_consume(aa, rsrca->local_header_offset - offset);
      }
      hsize = zip_get_local_file_header_size(aa, 0LL);
      _archive_read_consume(aa, hsize);
      remaining_bytes = rsrca->compressed_size;
      metadata_bytes = rsrca->uncompressed_size;
      mp = metadata;
      eof = 0;
      while ( 1 )
      {
        v5 = 0;
        if ( !eof )
          v5 = remaining_bytes != 0;
        if ( !v5 )
          break;
        p = (const unsigned __int8 *)_archive_read_ahead(aa, 1uLL, &bytes_avail);
        if ( !p )
        {
          archive_set_error(&aa->archive, 22, "Truncated ZIP file header");
          ret = -20;
          goto exit_mac_metadata;
        }
        if ( bytes_avail > remaining_bytes )
          bytes_avail = remaining_bytes;
        if ( rsrca->compression )
        {
          bytes_used = 0LL;
        }
        else
        {
          memcpy(mp, p, bytes_avail);
          bytes_used = bytes_avail;
          metadata_bytes -= bytes_avail;
          mp += bytes_avail;
          if ( !metadata_bytes )
            eof = 1;
        }
        _archive_read_consume(aa, bytes_used);
        remaining_bytes -= bytes_used;
      }
      archive_entry_copy_mac_metadata(entrya, metadata, rsrca->uncompressed_size - metadata_bytes);
exit_mac_metadata:
      _archive_read_seek(aa, offset, 0);
      zip->decompress_init = 0;
      free(metadata);
      return ret;
    }
    else
    {
      archive_set_error(&aa->archive, 12, "Can't allocate memory for Mac metadata");
      return -30;
    }
  }
  else
  {
    archive_set_error(&aa->archive, 22, "Mac metadata is too large: %jd > 4M bytes", rsrca->uncompressed_size);
    return -20;
  }
}