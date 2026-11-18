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
  int v10; // eax
  int num_verticesa; // [rsp+14h] [rbp-Ch]
  int num_verticesb; // [rsp+14h] [rbp-Ch]

  num_verticesa = num_vertices;
  if ( start_off )
  {
    if ( was_off )
    {
      num_verticesa = num_vertices + 1;
      stbtt_setvertex(&vertices[num_vertices], 3u, (scx + cx_0) >> 1, (scy + cy) >> 1, cx_0, cy);
    }
    v10 = num_verticesa;
    num_verticesb = num_verticesa + 1;
    stbtt_setvertex(&vertices[v10], 3u, sx, sy, scx, scy);
  }
  else
  {
    num_verticesb = num_vertices + 1;
    if ( was_off )
      stbtt_setvertex(&vertices[num_vertices], 3u, sx, sy, cx_0, cy);
    else
      stbtt_setvertex(&vertices[num_vertices], 2u, sx, sy, 0, 0);
  }
  return num_verticesb;
}