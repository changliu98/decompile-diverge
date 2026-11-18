static bool resize_vbar_entry(RDPCLIENT * This, vbar_t *vbar)
{
 unsigned int bpp;
 unsigned int old_size;
 unsigned int diff_size;
 char *new_ptr;
 bool result;

 if (vbar->alloc > vbar->size)
 {
  bpp = FreeRDPGetBytesPerPixel(This->server_depth);
  old_size = vbar->size * bpp;
  diff_size = (vbar->alloc - vbar->size) * bpp;
  vbar->size = vbar->alloc;

  new_ptr = (char *) _ZN4chip9ArgParser11HelpOptionsC2EPKcS3_S3_(vbar->ptr, vbar->alloc, bpp, 32);

  if (!new_ptr)
  {
   result = false;
  }
  else
  {
   memset(new_ptr + old_size, 0, diff_size);
   vbar->ptr = new_ptr;
  }
 }

 if (!vbar->ptr && vbar->size != 0)
 {
  result = false;
 }
 else
 {
  result = true;
 }

 return result;
}