void __cdecl delete_buff_tail(buffheader_T *buf, int slen)
{
  int len; // [rsp+0h] [rbp-10h]

  len = strlen((const char *)buf->bh_curr->b_str);
  if ( len >= slen )
  {
    buf->bh_curr->b_str[len - slen] = 0;
    buf->bh_space += slen;
  }
}