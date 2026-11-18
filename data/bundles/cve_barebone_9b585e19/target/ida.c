int __cdecl archive_read_format_rar_read_data(archive_read *a, const void **buff, size_t *size, int64_t *offset)
{
  int compression_method; // [rsp+8h] [rbp-38h]
  int ret; // [rsp+Ch] [rbp-34h]
  rar *rar; // [rsp+10h] [rbp-30h]

  rar = (rar *)a->format->data;
  if ( rar->has_encrypted_entries == -1 )
    rar->has_encrypted_entries = 0;
  if ( rar->bytes_unconsumed > 0 )
  {
    _archive_read_consume(a, rar->bytes_unconsumed);
    rar->bytes_unconsumed = 0LL;
  }
  *buff = 0LL;
  if ( rar->entry_eof || rar->offset_seek >= rar->unp_size )
  {
    *size = 0LL;
    *offset = rar->offset;
    if ( *offset < rar->unp_size )
      *offset = rar->unp_size;
    return 1;
  }
  else
  {
    compression_method = rar->compression_method;
    if ( compression_method == 48 )
      return read_data_stored(a, buff, size, offset);
    if ( (unsigned int)(compression_method - 49) < 5 )
    {
      ret = read_data_compressed(a, buff, size, offset);
      if ( ret && ret != -20 )
        Ppmd7_Free(&rar->ppmd7_context);
    }
    else
    {
      archive_set_error(&a->archive, -1, "Unsupported compression method for RAR file.");
      return -30;
    }
    return ret;
  }
}