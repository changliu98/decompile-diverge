int __cdecl vips_source_read_to_memory(VipsSource *source)
{
  gint64 v1; // rax
  unsigned __int8 *q; // [rsp+28h] [rbp-28h]
  gint64 read_position; // [rsp+30h] [rbp-20h]
  GByteArray *byte_array; // [rsp+38h] [rbp-18h]

  if ( source->is_pipe )
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->is_pipe");
    abort();
  }
  if ( source->blob )
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->blob");
    abort();
  }
  if ( source->header_bytes )
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->header_bytes");
    abort();
  }
  if ( source->length < 0 )
  {
    fprintf(stderr, "assertion failed: %s\n", "source->length >= 0");
    abort();
  }
  if ( vips_source_rewind(source) )
    return -1;
  byte_array = g_byte_array_new();
  g_byte_array_set_size(byte_array, source->length);
  read_position = 0LL;
  for ( q = byte_array->data; ; q += v1 )
  {
    if ( read_position >= source->length )
    {
LABEL_22:
      source->data = byte_array->data;
      source->is_pipe = 0;
      source->header_bytes = byte_array;
      vips_source_minimise(source);
      return 0;
    }
    v1 = source->length - read_position >= 4096
       ? vips_source_read(source, q, source->length - read_position)
       : vips_source_read(source, q, 0x1000uLL);
    if ( v1 == -1 )
      break;
    if ( !v1 )
      goto LABEL_22;
    read_position += v1;
  }
  if ( byte_array )
    g_byte_array_unref(byte_array);
  return -1;
}