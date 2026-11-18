static int kwajd_read_headers(struct wav_reader *wr, struct fileio *fio,
      struct wav_header *wh)
{
 unsigned char buf[14];
 int i, j;
 char *p;
 long ofs;

 if (wr->fio_read(fio, buf, 14) != 14)
  return 3;

 if ((unsigned int)((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]) != (('W'<<24)|('A'<<16)|('V'<<8)|'E') ||
     (unsigned int)((buf[7] << 24) | (buf[6] << 16) | (buf[5] << 8) | buf[4]) != (('f'<<24)|('m'<<16)|('t'<<8)|' '))
  return 7;

 wh->format = (short)((buf[9] << 8) | buf[8]);
 wh->channels = (long)((buf[11] << 24) | (buf[10] << 16) | (buf[9] << 8) | buf[8]);
 wh->freq = (short)((buf[13] << 8) | buf[12]);
 wh->bpc = 0;
 wh->name = NULL;
 wh->len = 0;
 wh->extlen = 0;

 if (wh->format & 1) {
  if (wr->fio_read(fio, buf, 4) != 4)
   return 3;
  wh->bpc = (long)((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
 }

 if (wh->format & 2) {
  if (wr->fio_read(fio, buf, 2) != 2)
   return 3;
 } else if (wh->format & 4) {
  if (wr->fio_read(fio, buf, 2) != 2)
   return 3;
  i = (short)((buf[1] << 8) | buf[0]);
  if (wr->fio_seek(fio, i, 1))
   return 5;
 } else if (wh->format & (8|16)) {
  ofs = wr->fio_pos(fio);
  p = wr->alloc(wr, 13);
  if (!p)
   return 6;
  wh->name = p;
  if (wh->format & 8) {
   if (wr->fio_read(fio, buf, 9) != 9)
    return 3;
   for (i = 0; i < 9 && (*p = buf[i]); i++, p++);
   j = (i < 9) ? i + 1 : 9;
  } else {
   *p++ = '.';
   if (wr->fio_read(fio, buf, 4) != 4)
    return 3;
   for (i = 0; i < 4 && (*p = buf[i]); i++, p++);
   j = (i < 4) ? i + 1 : 4;
  }
  ofs += j;
  if (wr->fio_seek(fio, ofs, 0))
   return 5;
 } else
  *p = '\0';

 if (wh->format & 32) {
  if (wr->fio_read(fio, buf, 2) != 2)
   return 3;
  i = (short)((buf[1] << 8) | buf[0]);
  wh->len = wr->alloc(wr, i + 1);
  if (!wh->len)
   return 6;
  if (wr->fio_read(fio, wh->len, i) != i)
   return 3;
  wh->len[i] = '\0';
  wh->extlen = (short)i;
 }

 return 0;
}