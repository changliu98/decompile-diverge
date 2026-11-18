int __cdecl vips_source_read_to_memory(VipsSource *source)
{
  gint64 bytes_read;
  unsigned __int8 *buf_ptr;
  gint64 read_position;
  GByteArray *byte_array;

  // Assertions
  if (source->is_pipe)
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->is_pipe");
    abort();
  }
  if (source->blob)
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->blob");
    abort();
  }
  if (source->header_bytes)
  {
    fprintf(stderr, "assertion failed: %s\n", "!source->header_bytes");
    abort();
  }
  if (source->length < 0)
  {
    fprintf(stderr, "assertion failed: %s\n", "source->length >= 0");
    abort();
  }

  if (vips_source_rewind(source))
    return -1;

  byte_array = g_byte_array_new();
  g_byte_array_set_size(byte_array, source->length);
  
  read_position = 0LL;
  buf_ptr = byte_array->data;

  while (read_position < source->length)
  {
    // The ternary operator preserves the original logic where the condition 
    // determines the requested read size, but vips_source_read is always called.
    bytes_read = (source->length - read_position >= 4096)
               ? vips_source_read(source, buf_ptr, source->length - read_position)
               : vips_source_read(source, buf_ptr, 0x1000uLL);

    if (bytes_read == -1)
    {
      if (byte_array)
        g_byte_array_unref(byte_array);
      return -1;
    }

    if (!bytes_read)
      break;

    read_position += bytes_read;
    buf_ptr += bytes_read;
  }

  source->data = byte_array->data;
  source->is_pipe = 0;
  source->header_bytes = byte_array;
  vips_source_minimise(source);

  return 0;
}