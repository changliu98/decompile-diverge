int __cdecl stbtt__close_shape(
        stbtt_vertex *vertices,
        int num_vertices,
        int was_off,
        int start_off,
        stbtt_int32 sx,
        stbtt_int32 sy,
        stbtt_int32 scx,
        stbtt_int32 scy,
        stbtt_int32 cx_0,
        stbtt_int32 cy)
{
  if (start_off)
  {
    if (was_off)
    {
      stbtt_setvertex(&vertices[num_vertices], 3u, (scx + cx_0) >> 1, (scy + cy) >> 1, cx_0, cy);
      num_vertices++;
    }
    stbtt_setvertex(&vertices[num_vertices], 3u, sx, sy, scx, scy);
    return num_vertices + 1;
  }
  else
  {
    if (was_off)
      stbtt_setvertex(&vertices[num_vertices], 3u, sx, sy, cx_0, cy);
    else
      stbtt_setvertex(&vertices[num_vertices], 2u, sx, sy, 0, 0);
      
    return num_vertices + 1;
  }
}