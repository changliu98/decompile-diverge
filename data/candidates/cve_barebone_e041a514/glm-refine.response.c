int __cdecl gd2GetHeader(
        gdIOCtxPtr in,
        int *sx,
        int *sy,
        int *cs_0,
        int *vers,
        int *fmt,
        int *ncx,
        int *ncy,
        t_chunk_info **chunkIdx)
{
  int nc; 
  t_chunk_info *cidx; 
  char id[5]; 
  int ch_0; 
  int i; 

  // Read the 4-byte magic identifier ("gd2\0")
  for ( i = 0; i < 4; ++i )
  {
    ch_0 = gdGetC(in);
    if ( ch_0 == -1 )
      return 0;
    id[i] = ch_0;
  }
  id[4] = 0;

  // Validate the header fields sequentially
  if ( strcmp(id, "gd2")
    || gdGetWord(vers, in) != 1
    || (*vers != 1 && *vers != 2)
    || !gdGetWord(sx, in)
    || !gdGetWord(sy, in)
    || gdGetWord(cs_0, in) != 1
    || *cs_0 < 64
    || *cs_0 > 4096
    || gdGetWord(fmt, in) != 1
    || (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4)
    || gdGetWord(ncx, in) != 1
    || gdGetWord(ncy, in) != 1 )
  {
    return 0;
  }

  // If the format doesn't contain chunk index data, we are done
  if ( *fmt != 2 && *fmt != 4 )
    return 1;

  nc = *ncy * *ncx;
  
  // Check for integer overflow / non-positive size (8 * nc > 0)
  if ( 8 * nc > 0 )
  {
    cidx = (t_chunk_info *)calloc(8 * nc, 1uLL);
    for ( i = 0; i < nc; ++i )
    {
      if ( gdGetInt((int *)&cidx[i], in) != 1
        || gdGetInt(&cidx[i].size, in) != 1
        || cidx[i].offset < 0
        || cidx[i].size < 0 )
      {
        free(cidx);
        return 0;
      }
    }
    *chunkIdx = cidx;
    return 1;
  }

  return 0;
}