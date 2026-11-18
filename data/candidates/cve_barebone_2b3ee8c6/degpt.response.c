int zip_read_mac_metadata(archive_read *a,archive_entry *entry,zip_entry *rsrc)

{
  archive_read *a_00;
  char *pcVar1;
  size_t bytes_used;
  ssize_t bytes_avail;
  uchar *p;
  int eof;
  int ret;
  ssize_t hsize;
  size_t metadata_bytes;
  size_t remaining_bytes;
  int64_t offset;
  uchar *mp;
  uchar *metadata;
  zip *zip;
  zip_entry *rsrc_local;
  archive_entry *entry_local;
  archive_read *a_local;
  int local_c;
  
  zip = a->format->data;
  rsrc_local = rsrc;
  entry_local = entry;
  a_local = a;
  offset = archive_filter_bytes(&a->archive,0);
  a_00 = a_local;
  ret = 0;
  if (rsrc_local->compression == '\0') {
    if (rsrc_local->uncompressed_size < 0x400001) {
      metadata = malloc(rsrc_local->uncompressed_size);
      if (metadata == (uchar *)0x0) {
        archive_set_error(&a_local->archive,0xc,"Can\'t allocate memory for Mac metadata");
        local_c = -0x1e;
      }
      else {
        if (offset < rsrc_local->local_header_offset) {
          __archive_read_consume(a_local,rsrc_local->local_header_offset - offset);
        }
        else if (offset != rsrc_local->local_header_offset) {
          __archive_read_seek(a_local,rsrc_local->local_header_offset,0);
        }
        hsize = zip_get_local_file_header_size(a_local,0);
        __archive_read_consume(a_local,hsize);
        remaining_bytes = rsrc_local->compressed_size;
        metadata_bytes = rsrc_local->uncompressed_size;
        mp = metadata;
        eof = 0;
        for (; eof == 0 && remaining_bytes != 0; remaining_bytes = remaining_bytes - bytes_used) {
          p = __archive_read_ahead(a_local,1,&bytes_avail);
          if (p == (uchar *)0x0) {
            archive_set_error(&a_local->archive,0x16,"Truncated ZIP file header");
            ret = -0x14;
            goto LAB_00101911;
          }
          if (remaining_bytes < (ulong)bytes_avail) {
            bytes_avail = remaining_bytes;
          }
          if (rsrc_local->compression == '\0') {
            memcpy(mp,p,bytes_avail);
            bytes_used = bytes_avail;
            metadata_bytes = metadata_bytes - bytes_avail;
            mp = mp + bytes_avail;
            if (metadata_bytes == 0) {
              eof = 1;
            }
          }
          else {
            bytes_used = 0;
          }
          __archive_read_consume(a_local,bytes_used);
        }
        archive_entry_copy_mac_metadata
                  (entry_local,metadata,rsrc_local->uncompressed_size - metadata_bytes);
LAB_00101911:
        __archive_read_seek(a_local,offset,0);
        zip->decompress_init = '\0';
        free(metadata);
        local_c = ret;
      }
    }
    else {
      archive_set_error(&a_local->archive,0x16,"Mac metadata is too large: %jd > 4M bytes",
                        rsrc_local->uncompressed_size);
      local_c = -0x14;
    }
  }
  else {
    pcVar1 = compression_name((uint)rsrc_local->compression);
    archive_set_error(&a_00->archive,0x16,"Unsupported ZIP compression method (%s)",pcVar1);
    local_c = -0x14;
  }
  return local_c;
}