int __cdecl archive_read_format_rar_read_data(archive_read *a, const void **buff, size_t *size, int64_t *offset)
{
  int compression_method;
  int ret;
  rar *rar;

  rar = (rar *)a->format->data;
  
  // Initialize encrypted entries flag if undefined
  if (rar->has_encrypted_entries == -1)
    rar->has_encrypted_entries = 0;
    
  // Consume any previously unconsumed bytes
  if (rar->bytes_unconsumed > 0)
  {
    _archive_read_consume(a, rar->bytes_unconsumed);
    rar->bytes_unconsumed = 0LL;
  }
  
  *buff = 0LL;
  
  // Check for End-of-File or if seek offset exceeds uncompressed size
  if (rar->entry_eof || rar->offset_seek >= rar->unp_size)
  {
    *size = 0LL;
    *offset = rar->offset;
    if (*offset < rar->unp_size)
      *offset = rar->unp_size;
    return 1; // ARCHIVE_EOF
  }
  
  compression_method = rar->compression_method;
  
  // Method 48 (0x30): Stored / No compression
  if (compression_method == 48)
    return read_data_stored(a, buff, size, offset);
    
  // Methods 49-53 (0x31 - 0x35): Compressed
  if ((unsigned int)(compression_method - 49) < 5)
  {
    ret = read_data_compressed(a, buff, size, offset);
    // If an error occurred (and it's not a simple "truncated" error), free the PPMd context
    if (ret && ret != -20)
      Ppmd7_Free(&rar->ppmd7_context);
    return ret;
  }
  
  // Unsupported compression method
  archive_set_error(&a->archive, -1, "Unsupported compression method for RAR file.");
  return -30; // ARCHIVE_FAILED
}