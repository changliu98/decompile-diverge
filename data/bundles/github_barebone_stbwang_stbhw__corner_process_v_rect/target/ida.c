void __cdecl stbhw__corner_process_v_rect(
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
  stbhw__draw_hline(p->data, p->stride, xpos + 1, ypos, stbhw__corner_colors_to_edge_color[4 * a + d], len, 0);
  stbhw__draw_vline(p->data, p->stride, xpos, ypos + 1, stbhw__corner_colors_to_edge_color[4 * a + b], len, 5);
  stbhw__draw_vline(p->data, p->stride, len + xpos + 1, ypos + 1, stbhw__corner_colors_to_edge_color[4 * d + e], len, 1);
  stbhw__draw_vline(p->data, p->stride, xpos, len + ypos + 1, stbhw__corner_colors_to_edge_color[4 * b + c], len, 4);
  stbhw__draw_vline(
    p->data,
    p->stride,
    len + xpos + 1,
    len + ypos + 1,
    stbhw__corner_colors_to_edge_color[4 * e + f],
    len,
    5);
  stbhw__draw_hline(
    p->data,
    p->stride,
    xpos + 1,
    2 * len + ypos + 1,
    stbhw__corner_colors_to_edge_color[4 * c + f],
    len,
    3);
  if ( p->c->corner_type_color_template[0][a] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, 1, 1);
  if ( p->c->corner_type_color_template[3][b] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, 1, len + 1);
  if ( p->c->corner_type_color_template[2][c] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, 1, 2 * len + 1);
  if ( p->c->corner_type_color_template[1][d] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, len + 1, 1);
  if ( p->c->corner_type_color_template[0][e] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, len + 1, len + 1);
  if ( p->c->corner_type_color_template[3][f] )
    stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, 2 * len, len + 1, 2 * len + 1);
  stbhw__set_pixel(p->data, p->stride, xpos, ypos, &stbhw__corner_colors[3 * a]);
  stbhw__set_pixel(p->data, p->stride, xpos, len + ypos, &stbhw__corner_colors[3 * b + 36]);
  stbhw__set_pixel(p->data, p->stride, xpos, 2 * len + ypos + 1, &stbhw__corner_colors[3 * c + 24]);
  stbhw__set_pixel(p->data, p->stride, len + xpos + 1, ypos, &stbhw__corner_colors[3 * d + 12]);
  stbhw__set_pixel(p->data, p->stride, len + xpos + 1, len + ypos, &stbhw__corner_colors[3 * e]);
  stbhw__set_pixel(p->data, p->stride, len + xpos + 1, 2 * len + ypos + 1, &stbhw__corner_colors[3 * f + 36]);
}