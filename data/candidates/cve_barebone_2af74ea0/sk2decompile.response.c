int vips_source_read_to_memory(VipsSource *source) {
  GByteArray *blob;
  unsigned char *p;
  off_t nread;
  off_t n;
  if (!(!source->is_pipe)) {
    fprintf(stderr, "assertion failed: %s\n", "!source->is_pipe");
    abort();
  };
  if (!(!source->blob)) {
    fprintf(stderr, "assertion failed: %s\n", "!source->blob");
    abort();
  };
  if (!(!source->header_bytes)) {
    fprintf(stderr, "assertion failed: %s\n", "!source->header_bytes");
    abort();
  };
  if (!(source->length >= 0)) {
    fprintf(stderr, "assertion failed: %s\n", "source->length >= 0");
    abort();
  };
  if (vips_source_rewind(source)) return -1;
  blob = g_byte_array_new();
  g_byte_array_set_size(blob, source->length);
  nread = 0;
  p = blob->data;
  while (nread < source->length) {
    n = vips_source_read(
        source, p,
        (((4096) < (source->length - nread)) ? (4096)
                                             : (source->length - nread)));
    if (n == -1) {
      if (blob) g_byte_array_unref(blob);
      return -1;
    }
    if (n == 0) break;
    nread += n;
    p += n;
  }
  source->buffer = blob->data;
  source->is_pipe = false;
  source->header_bytes = blob;
  vips_source_minimise(source);
  return 0;
}