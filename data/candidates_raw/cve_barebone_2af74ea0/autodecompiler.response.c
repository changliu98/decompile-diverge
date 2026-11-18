static int
vips_source_load_blob(VipsSource *source)
{
 GByteArray *array;
 gsize len;
 unsigned char *p;
 off_t i;
 size_t result;

 do { if (!(source)) { ; abort(); } } while(0);
 do { if (!(!source->is_pipe)) { ; abort(); } } while(0);
 do { if (!(!source->blob)) { ; abort(); } } while(0);
 do { if (!(!source->header_bytes)) { ; abort(); } } while(0);
 do { if (!(source->length >= 0)) { ; abort(); } } while(0);

 if (vips_source_rewind(source))
  return -1;

 array = g_byte_array_new();
 g_byte_array_set_size(array, (guint) source->length);

 i = 0;
 p = array->data;
 while (i < source->length) {
  VipsSource *sub = (VipsSource *) source;
  size_t len;
  size_t result;

  if (len > source->length - i)
   len = source->length - i;

  result = vips_source_read(sub, p, len);
  if (result == (size_t) -1) {
  fail:
   if (array)
    g_byte_array_unref(array);
   array = NULL;
   return -1;
  }

  if (result == 0)
   break;

  i += result;
  p += result;
 }

 source->data = array->data;
 source->is_pipe = 0;
 source->header_bytes = array;
 vips_source_minimise(source);

 return 0;
}