int vips_source_read_to_memory(VipsSource *source)

{
  int iVar1;
  GByteArray *array;
  gint64 gVar2;
  size_t local_50;
  gint64 bytes_read;
  uchar *q;
  gint64 read_position;
  GByteArray *byte_array;
  VipsSource *source_local;
  int local_c;
  
  if (source->is_pipe != 0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"assertion failed: %s\n","!source->is_pipe");
                    /* WARNING: Subroutine does not return */
    abort();
  }
  if (source->blob != (VipsBlob *)0x0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"assertion failed: %s\n","!source->blob");
                    /* WARNING: Subroutine does not return */
    abort();
  }
  if (source->header_bytes != (GByteArray *)0x0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"assertion failed: %s\n","!source->header_bytes");
                    /* WARNING: Subroutine does not return */
    abort();
  }
  if (source->length < 0) {
    fprintf(*(FILE **)PTR_stderr_00103ff8,"assertion failed: %s\n","source->length >= 0");
                    /* WARNING: Subroutine does not return */
    abort();
  }
  iVar1 = vips_source_rewind(source);
  if (iVar1 == 0) {
    array = g_byte_array_new();
    g_byte_array_set_size(array,(guint)source->length);
    read_position = 0;
    q = array->data;
    for (; read_position < source->length; read_position = gVar2 + read_position) {
      if (source->length - read_position < 0x1000) {
        local_50 = 0x1000;
      }
      else {
        local_50 = source->length - read_position;
      }
      gVar2 = vips_source_read(source,q,local_50);
      if (gVar2 == -1) {
        if (array != (GByteArray *)0x0) {
          g_byte_array_unref(array);
        }
        return -1;
      }
      if (gVar2 == 0) break;
      q = q + gVar2;
    }
    source->data = array->data;
    source->is_pipe = 0;
    source->header_bytes = array;
    vips_source_minimise(source);
    local_c = 0;
  }
  else {
    local_c = -1;
  }
  return local_c;
}