static int am_writestring(am_writer *w, const char *s) {
  am_io *io = w->io;
  size_t len;
  size_t used;
  if (s)
    len = strlen(s);
  else
    len = 0;
  if (len >= 256) return -1;
  if (len < 32) {
    if (am_writechar(w, 0xa0 + len)) return -1;
  } else {
    if (am_writechar(w, 0xd9)) return -1;
    if (am_writechar(w, len)) return -1;
  }
  used = w->p - w->buf;
  if (used + len > 4096) {
    w->p = w->buf;
    if (used) {
      w->err = io->write(io, w->buf, used);
      if (w->err) return -1;
    }
  }
  memcpy(w->p, s, len);
  w->p += len;
  return 0;
}