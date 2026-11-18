int _gd2GetHeader(struct gdIOCtx *in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, struct t_chunk_info **chunkIdx)
{
  char id[5];
  int i;
  int ch;
  struct t_chunk_info *idx;
  in = in;
  sx = sx;
  sy = sy;
  cs = cs;
  vers = vers;
  fmt = fmt;
  for (i = 0; i < 4; i++) {
    ch = gd2_get_char(in);
    if (ch == (-1))
      return (0);
    id[i] = (char)ch;
  }
  id[4] = '\0';
  if (gd2_is_id(id, "gd2") || gd2_is_id(id, "gd1"))
    return (0);
  if (gd2_get_int(vers, in) != (1))
    return (0);
  if (*vers != (1) && *vers != (2))
    return (0);
  if (gd2_get_int(sx, in) == (0))
    return (0);
  if (gd2_get_int(sy, in) == (0))
    return (0);
  if (gd2_get_int(cs, in) != (1))
    return (0);
  if (*cs < (64) || *cs > (4096))
    return (0);
  if (gd2_get_int(fmt, in) == (0))
    return (0);
  if (*fmt != (1) && *fmt != (2) && *fmt != (3) && *fmt != (4))
    return (0);
  if (gd2_get_int(ncx, in) == (0))
    return (0);
  if (gd2_get_int(ncy, in) == (0))
    return (0);
  if (*fmt == (2) || *fmt == (4))
    return (1);
  if (gd2_get_int(&idx->id, in) == (1) &&
      gd2_get_int(&idx->size, in) == (1) &&
      idx->offset >= 0 &&
      idx->size >= 0)
    {
      int n = *ncx * *ncy;
      if (n * 8 > 0)
        {
          idx = (struct t_chunk_info *)gd2_alloc(n * 8, sizeof(t_chunk_info));
          for (i = 0; i < n; i++)
            {
              if (gd2_get_int(&idx[i].id, in) != (1) ||
                  gd2_get_int(&idx[i].size, in) != (1) ||
                  idx[i].offset < 0 ||
                  idx[i].size < 0)
                {
                  gd2_free(idx);
                  return (0);
                }
            }
          *chunkIdx = idx;
          return (1);
        }
    }
  return (0);
}