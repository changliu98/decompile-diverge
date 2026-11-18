int resp_add_size(struct resp_response *r, unsigned int add_size)
{
  unsigned int new_size = r->buf_size;
  char *new_buf;
  while (new_size < r->used_size + add_size)
    new_size *= 2;
  new_buf = realloc(r->buf, new_size);
  if (new_buf == ((void *)0))
    return -1;
  r->buf = new_buf;
  r->buf_size = new_size;
  return 0;
}