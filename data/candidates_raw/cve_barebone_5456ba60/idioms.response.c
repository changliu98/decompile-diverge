int mspack_read_header(struct mspack_system *sys, struct mspack_file *file, struct mskwajd_header *header)
{
  unsigned char buf[16];
  int i; int len;
  if (sys->read (file, buf, 14) != 14)
    return 3;
  if (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24) != 0x4a574143
      || buf[4] | (buf[5] << 8) | (buf[6] << 16) | (buf[7] << 24) != 0xa1e1e1e1)
    return 7;
  header->comp_type = (buf[8] | (buf[9] << 8));
  header->data_offset = (buf[10] | (buf[11] << 8));
  header->headers = (buf[12] | (buf[13] << 8));
  header->length = 0;
  header->filename = ((void *)0);
  header->extra = ((void *)0);
  header->extra_length = 0;
  if (header->headers & 1)
  {
    if (sys->read (file, buf, 4) != 4)
      return 3;
    header->length = (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
  }
  if (header->headers & 2)
  {
    if (sys->read (file, buf, 2) != 2)
      return 3;
  }
  if (header->headers & 4)
  {
    if (sys->read (file, buf, 2) != 2)
      return 3;
    if (sys->seek (file, (buf[0] | (buf[1] << 8)), 1))
      return 5;
  }
  if (header->headers & (8 | 16))
  {
    long offset = sys->tell (file);
    char *name = (char *)sys->alloc (sys, 12 + 1);
    if (name == ((void *)0))
      return 6;
    header->filename = name;
    if (header->headers & 8)
    {
      if (sys->read (file, buf, 9) != 9)
        return 3;
      for (i = 0; i < 9; i++)
      {
        if ((buf[i] = *name++) == '\0')
          break;
      }
      len = i < 9 ? i + 1 : 9;
      if (sys->seek (file, offset + len, 0))
        return 5;
    }
    if (header->headers & 16)
    {
      *name++ = '.';
      if (sys->read (file, buf, 4) != 4)
        return 3;
      for (i = 0; i < 4; i++)
      {
        if ((buf[i] = *name++) == '\0')
          break;
      }
      len = i < 4 ? i + 1 : 4;
      if (sys->seek (file, offset + len, 0))
        return 5;
    }
    *name = '\0';
  }
  if (header->headers & 32)
  {
    if (sys->read (file, buf, 2) != 2)
      return 3;
    len = (buf[0] | (buf[1] << 8));
    header->extra = (char *)sys->alloc (sys, len + 1);
    if (header->extra == ((void *)0))
      return 6;
    if (sys->read (file, header->extra, len) != len)
      return 3;
    header->extra[len] = '\0';
    header->extra_length = len;
  }
  return 0;
}