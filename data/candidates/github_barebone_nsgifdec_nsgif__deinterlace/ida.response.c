bool __cdecl nsgif__deinterlace(uint32_t height, uint32_t *y, uint8_t *step)
{
  int v4; // [rsp+0h] [rbp-1Ch]

  *y += *step & 0xF;
  if ( *y >= height )
  {
    v4 = *step;
    if ( v4 != 4 )
    {
      if ( v4 != 8 )
      {
        if ( v4 != 24 )
          return 0;
        *y = 4;
        *step = 8;
        if ( *y < height )
          return 1;
      }
      *y = 2;
      *step = 4;
      if ( *y < height )
        return 1;
    }
    *y = 1;
    *step = 2;
    return *y < height;
  }
  return 1;
}