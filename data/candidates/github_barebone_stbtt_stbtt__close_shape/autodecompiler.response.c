static int stbtt__close_shape(stbtt_vertex *vertices, int num_vertices, int was_off, int start_off,
    int sx, int sy, int scx, int scy, int cx, int cy)
{
   if (start_off) {
      if (was_off)
         stbtt_setvertex(&vertices[num_vertices++], 3, (cx+scx)>>1, (cy+scy)>>1, cx,cy);
      stbtt_setvertex(&vertices[num_vertices++], 3, sx,sy,scx,scy);
   } else {
      if (was_off)
         stbtt_setvertex(&vertices[num_vertices++], 3, sx,sy,cx,cy);
      else
         stbtt_setvertex(&vertices[num_vertices++], 2, sx,sy,0,0);
   }
   return num_vertices;
}