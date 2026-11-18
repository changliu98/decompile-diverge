void delete_buff_tail(buffheader_T *buf,int slen)

{
  size_t sVar1;
  int len;
  int slen_local;
  buffheader_T *buf_local;
  
  sVar1 = strlen((char *)buf->bh_curr->b_str);
  if (slen <= (int)sVar1) {
    buf->bh_curr->b_str[(int)sVar1 - slen] = '\0';
    buf->bh_space = slen + buf->bh_space;
  }
  return;
}