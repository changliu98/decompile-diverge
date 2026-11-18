void __cdecl stbhw__corner_process_h_rect(
        stbhw__process *p,
        int xpos,
        int ypos,
        int a,
        int b,
        int c,
        int d,
        int e,
        int f)
{
  int len; // [rsp+10h] [rbp-20h]

  len = p->c->short_side_len;
  stbhw__draw_hline(p->data, p->stride, xpos + 1, ypos, stbhw__corner_colors_to_edge_color[4 * a + b], len, 2);
  stbhw__draw_hline(p->data, p->stride, len + xpos + 1, ypos, stbhw__corner_colors_to_edge_color[4 * b + c], len, 3);
  stbhw__draw_vline(p->data, p->stride, xpos, ypos + 1, stbhw__corner_colors_to_edge_color[4 * a + d], len, 1);
  stbhw__draw_vline(
    p->data,
    p->stride,
    2 * len + xpos + 1,
    ypos + 1,
    stbhw__corner_colors_to_edge_color[4 * c + f],
    len,
    4);
  stbhw__draw_hline(p->data, p->stride, xpos + 1, len + ypos + 1, stbhw__corner_colors_to_edge_color[4 * d + e], len, 0);
  stbhw__draw_hline(
    p->data,
    p->stride,
    len + xpos + 1,
    len + ypos + 1,
    stbhw__corner_colors_to_edge_color[4 * e + f],
    len,
    2);
  if ( p->c->corner_type_color_template[1][a] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, 1, 1);
  if ( p->c->corner_type_color_template[2][b] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, len + 1, 1);
  if ( p->c->corner_type_color_template[3][c] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, 2 * len + 1, 1);
  if ( p->c->corner_type_color_template[0][d] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, 1, len + 1);
  if ( p->c->corner_type_color_template[1][e] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, len + 1, len + 1);
  if ( p->c->corner_type_color_template[2][f] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, 2 * len, len, 2 * len + 1, len + 1);
  stbhw__set_pixel(p->data, p->stride, xpos, ypos, &stbhw__corner_colors[3 * a + 12]);
  stbhw__set_pixel(p->data, p->stride, len + xpos, ypos, &stbhw__corner_colors[3 * b + 24]);
  stbhw__set_pixel(p->data, p->stride, 2 * len + xpos + 1, ypos, &stbhw__corner_colors[3 * c + 36]);
  stbhw__set_pixel(p->data, p->stride, xpos, len + ypos + 1, &stbhw__corner_colors[3 * d]);
  stbhw__set_pixel(p->data, p->stride, len + xpos, len + ypos + 1, &stbhw__corner_colors[3 * e + 12]);
  stbhw__set_pixel(p->data, p->stride, 2 * len + xpos + 1, len + ypos + 1, &stbhw__corner_colors[3 * f + 24]);
}