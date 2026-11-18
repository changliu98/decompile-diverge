int stbtt__close_shape(stbtt_vertex *vertices,int num_vertices,int was_off,int start_off,
                      stbtt_int32 sx,stbtt_int32 sy,stbtt_int32 scx,stbtt_int32 scy,stbtt_int32 cx,
                      stbtt_int32 cy)

{
  stbtt_int32 sy_local;
  stbtt_int32 sx_local;
  int start_off_local;
  int was_off_local;
  int num_vertices_local;
  stbtt_vertex *vertices_local;
  
  num_vertices_local = num_vertices;
  if (start_off == 0) {
    if (was_off == 0) {
      stbtt_setvertex(vertices + num_vertices,'\x02',sx,sy,0,0);
    }
    else {
      stbtt_setvertex(vertices + num_vertices,'\x03',sx,sy,cx,cy);
    }
  }
  else {
    if (was_off != 0) {
      num_vertices_local = num_vertices + 1;
      stbtt_setvertex(vertices + num_vertices,'\x03',cx + scx >> 1,cy + scy >> 1,cx,cy);
    }
    stbtt_setvertex(vertices + num_vertices_local,'\x03',sx,sy,scx,scy);
  }
  num_vertices_local = num_vertices_local + 1;
  return num_vertices_local;
}