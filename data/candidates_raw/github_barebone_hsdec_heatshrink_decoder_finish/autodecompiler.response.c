int heatshrink_decoder_finish(struct heatshrink_decoder *hsd)
{
 int ret;

 if(hsd == NULL)
 {
  ret = -1;
  goto out;
 }

 unsigned int len = hsd->buffer_size;
 if(len != 0)
 {
  while(len--);
  if(len == 0)
  {
   ret = hsd->head_pos || hsd->tail_pos ? 1 : 0;
  }
  else
  {
   ret = 1;
  }
 }
 else
 {
  ret = hsd->head_pos || hsd->tail_pos ? 1 : 0;
 }

out:
 return ret;
}