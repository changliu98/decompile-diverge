int _gd2GetHeader(struct gdIOCtx *in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, struct t_chunk_info **chunkIdx)
{
  int i;
  int c;
  char id[5];
  struct t_chunk_info *idx;
  struct gdIOCtx *in2 = in;
  int *sx2 = sx;
  int *sy2 = sy;
  int *cs2 = cs;
  int *vers2 = vers;
  int *fmt2 = fmt;
  for (i = 0; i < 4; i++)
  {
    if ((c = read_char(in2)) == (-1))
      return 0;
    id[i] = c;
  }
  id[4] = '\0';
  if (id_cmp(id, "gd2") == 0)
  {
    if (read_int(vers2, in2) == 1 && (*vers2 == 1 || *vers2 == 2))
    {
      if (read_int(sx2, in2) == 1 && read_int(sy2, in2) == 1)
      {
        if (read_int(cs2, in2) == 1 && *cs2 >= 64 && *cs2 <= 4096)
        {
          if (read_int(fmt2, in2) == 1 && (*fmt2 == 1 || *fmt2 == 2 || *fmt2 == 3 || *fmt2 == 4))
          {
            if (read_int(ncx, in2) == 1 && read_int(ncy, in2) == 1)
            {
              int nc = *ncx * *ncy;
              if (read_int(nc * sizeof(t_chunk_info), &idx) == 1 && idx != ((void *)0))
              {
                for (i = 0; i < nc; i++)
                {
                  if (read_int((char *) &idx[i].id, in2) != 1
                      || read_int((char *) &idx[i].size, in2) != 1
                      || idx[i].offset < 0
                      || idx[i].size < 0)
                  {
                    gd2_free_chunk_info(idx);
                    return 0;
                  }
                }
                *chunkIdx = idx;
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}