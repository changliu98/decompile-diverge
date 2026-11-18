static int
read_data(struct archive_read *a, char **buff, size_t *size, int64_t *offset)
{
 struct rar *rar = (struct rar *)(a->format->data);
 int ret;
 int comp_method;

 if(rar->main.endarc == -1)
  rar->main.endarc = 0;

 if(rar->skips > 0) {
  __archive_read_consume(a, rar->skips);
  rar->skips = 0;
 }

 *buff = NULL;

 if((rar->main.split != '\0') || (rar->main.split_offset >= rar->main.uncomp_size)) {
  *size = 0;
  *offset = rar->main.split_offset;
  if(*offset < rar->main.uncomp_size)
   *offset = rar->main.uncomp_size;
  ret = 1;
 } else {
  comp_method = rar->main.split_offset[23];
  switch(comp_method) {
  case '0':
   ret = read_data_stored(a, buff, size, offset);
   break;
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
   ret = read_data_compressed(a, buff, size, offset);
   if(ret != 0 && ret != -20)
    Ppmd7_Free(&rar->ppmd7_context);
   break;
  default:
   archive_set_error(&a->archive, -1,
       "Unsupported compression method for RAR file.");
   ret = -30;
  }
 }

 return ret;
}