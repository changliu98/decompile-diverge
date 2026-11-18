static int stbtt__close_shape(stbtt_vertex *vertices, int num_vertices,
                              int last_move_to, int last_move_to_missing,
                              stbtt_int32 x0, stbtt_int32 y0, stbtt_int32 x1,
                              stbtt_int32 y1, stbtt_int32 x2, stbtt_int32 y2) {
  if (last_move_to_missing) {
    if (last_move_to) {
      stbtt_setvertex(vertices + num_vertices++, 3, (x1 + x2) >> 1,
                      (y1 + y2) >> 1, x2, y2);
    }
    stbtt_setvertex(vertices + num_vertices++, 3, x0, y0, x1, y1);
  } else {
    if (last_move_to)
      stbtt_setvertex(vertices + num_vertices++, 3, x0, y0, x2, y2);
    else
      stbtt_setvertex(vertices + num_vertices++, 2, x0, y0, 0, 0);
  }
  return num_vertices;
}