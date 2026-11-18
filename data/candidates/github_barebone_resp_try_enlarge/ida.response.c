int __cdecl try_enlarge(RespResponse *r, uint32_t add_size)
{
  char *more_buf; // [rsp+0h] [rbp-20h]
  uint32_t new_size; // [rsp+8h] [rbp-18h]

  for ( new_size = r->buf_size; new_size < add_size + r->used_size; new_size *= 2 )
    ;
  more_buf = (char *)realloc(r->buf, new_size);
  if ( !more_buf )
    return -1;
  r->buf = more_buf;
  r->buf_size = new_size;
  return 0;
}