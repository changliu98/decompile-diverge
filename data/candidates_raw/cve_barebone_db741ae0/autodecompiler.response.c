int buffer_path_decode_slashes(buffer * const b, int pos, int i) {
 char * const s = b->ptr;
 int len = buffer_string_length(b);
 int u, j;

 if (pos < 0)
  u = len;
 else
  u = pos;

 j = i;
 for (;;) {
  while (i < u) {
   s[j] = s[i];
   if (s[i] == '%' && s[i+1] == '2' && s[i+2] == 'F') {
    s[j] = '/';
    i += 2;
   }
   ++i;
   ++j;
  }

  if (pos >= 0) {
   memmove(s+j, s+pos, len-pos);
   j += len-pos;
  }
  buffer_string_set_length(b, j);
  return pos;
}