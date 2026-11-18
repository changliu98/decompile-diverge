static void mobi_buffer_move(buffer_t *b, int offset, size_t len)
{
 size_t uoffset = (size_t)abs(offset);
 char *ptr = b->data + b->pos;
 if (offset >= 0) {
  if (b->pos + uoffset + len > b->size) {
   b->error = 9;
   return;
  }
  ptr += uoffset;
 } else {
  if (b->pos < uoffset) {
   b->error = 9;
   return;
  }
  ptr -= uoffset;
 }
 memmove(b->data + b->pos, ptr, len);
 b->pos += len;
}