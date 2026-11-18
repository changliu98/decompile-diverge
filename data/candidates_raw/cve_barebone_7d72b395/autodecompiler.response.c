static int read_header(struct wavinfo *w, struct chunk *c)
{
 int i, nchans, err;
 unsigned char *p;
 int len = c->len;
 p = c->data;

 w->fmt = 1;
 w->offset = 0;
 w->length = 0;
 w->chanmap = 0;

 if (w->chanmap) {
  free(w->chanmap);
  w->chanmap = NULL;
 }

 if (len) {
  w->chanmap = *p++;
  w->length = (w->length & ~0xff) | *p++;
  len -= 2;
  if (!len)
   return 0;
  w->offset = (*p++ << 16);
  len--;
  if (!len) {
   w->offset += w->offsetbase;
   goto done;
  }
  nchans = *p++;
  len--;
  if (!len) {
   w->offset += w->offsetbase;
   goto done;
  }
  if (len > nchans) {
   err = 0;
   goto done;
  }
  w->chanmap = malloc(nchans);
  if (!w->chanmap)
   goto done;
  for (i = 0; ; i++) {
   if (i >= nchans)
    break;
   if (len) {
    w->chanmap[i] = *p++;
    len--;
   } else
    w->chanmap[i] = i;
  }
 }
 err = 1;
done:
 return err;
}