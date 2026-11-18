static int read_new_config_info(struct wavinfo *w, struct chunk *c)
{
 int i, nchans, err;
 unsigned char *p;
 int len = c->len;
 p = c->data;

 w->valid = 1;
 w->offset = 0;
 w->bps = 0;
 w->fmt = 0;

 if (w->chanmap) {
  free(w->chanmap);
  w->chanmap = NULL;
 }

 if (len) {
  w->fmt = *p++;
  w->bps = w->bps & ~0xff | *p++;
  len -= 2;
  if (!len)
   return 0;

  w->offset = *p++ << 16;
  len--;
  if (!len) {
   w->offset += w->offset_extra;
   goto done;
  }

  nchans = *p++;
  w->offset += nchans;
  len--;
  if (!len)
   goto done;

  if (len > nchans) {
   err = 0;
   goto done;
  }

  w->chanmap = (char *)malloc(nchans);
  if (!w->chanmap)
   goto done;

  for (i = 0; i < nchans; i++) {
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