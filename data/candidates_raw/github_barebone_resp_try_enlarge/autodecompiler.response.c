int
grow_buffer(struct buffer *b, unsigned int len)
{
 char *new_data;
 unsigned int new_size;
 int ret;

 new_size = b->size;
 while (1) {
  if (new_size > b->len + len) {
   new_size *= 2;
  } else {
   break;
  }
 }

 new_data = realloc(b->data, new_size);
 if (!new_data) {
  ret = -1;
 } else {
  b->data = new_data;
  b->size = new_size;
  ret = 0;
 }

 return ret;
}