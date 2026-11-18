void sha1_update(sha1_context *s, unsigned char *data, size_t len)
{
 size_t i = 0;

 while (i < len) {
  s->buf[s->buflen] = data[i];
  s->buflen++;
  if (s->buflen == 64) {
   sha1_transform(s, s->buf);
   s->len += 512;
   s->buflen = 0;
  }
  i++;
 }
}