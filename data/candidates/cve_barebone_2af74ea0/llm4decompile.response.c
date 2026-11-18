int
vips_source_read_to_memory (VipsSource *source)
{
  GByteArray *bytes;
  unsigned char *p;
  gint64 bytes_read;
  gint64 read_position;
  int result;

  do { if (!(!source->is_pipe)) { fprintf(stderr, "assertion failed: %s\n", "!source->is_pipe"); abort(); } } while (0);
  do { if (!(!source->blob)) { fprintf(stderr, "assertion failed: %s\n", "!source->blob"); abort(); } } while (0);
  do { if (!(!source->header_bytes)) { fprintf(stderr, "assertion failed: %s\n", "!source->header_bytes"); abort(); } } while (0);
  do { if (!(source->length >= 0)) { fprintf(stderr, "assertion failed: %s\n", "source->length >= 0"); abort(); } } while (0);

  result = vips_source_rewind (source);
  if (result != 0)
    return -1;

  bytes = g_byte_array_new ();
  g_byte_array_set_size (bytes, source->length);
  p = bytes->data;
  read_position = 0;

  while (read_position < source->length) {
    gint64 block_size = ((4096) < (source->length - read_position) ? (4096) : (source->length - read_position));

    bytes_read = vips_source_read (source, p, block_size);

    if (bytes_read == -1) {
      if (bytes)
        g_byte_array_unref (bytes);
      return -1;
    }

    if (bytes_read == 0)
      break;

    p += bytes_read;
    read_position += bytes_read;
  }

  source->data = bytes->data;
  source->is_pipe = 0;
  source->header_bytes = bytes;
  vips_source_minimise (source);

  return 0;
}