void stbhw__corner_process_v_rect(stbhw__process *p, int xpos, int ypos, int a, int b, int c, int d, int e, int f)
{
   int len = p->c->short_side_len;
   stbhw__draw_hline(p->data, p->stride, xpos+1, ypos, stbhw__corner_colors_to_edge_color[a][d], len, 0);
   stbhw__draw_vline(p->data, p->stride, xpos, ypos+1, stbhw__corner_colors_to_edge_color[a][b], len, 5);
   stbhw__draw_vline(p->data, p->stride, xpos+len+1, ypos+1, stbhw__corner_colors_to_edge_color[d][e], len, 1);
   stbhw__draw_vline(p->data, p->stride, xpos, ypos+len+1, stbhw__corner_colors_to_edge_color[b][c], len, 4);
   stbhw__draw_vline(p->data, p->stride, xpos+len+1, ypos+len+1, stbhw__corner_colors_to_edge_color[e][f], len, 5);
   stbhw__draw_hline(p->data, p->stride, xpos+1, ypos+len*2+1, stbhw__corner_colors_to_edge_color[c][f], len, 3);

   if (p->c->corner_type_color_template[0][a])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, 1, 1);
   if (p->c->corner_type_color_template[3][b])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, 1, len+1);
   if (p->c->corner_type_color_template[2][c])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, 1, len*2+1);
   if (p->c->corner_type_color_template[1][d])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, len+1, 1);
   if (p->c->corner_type_color_template[0][e])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, len+1, len+1);
   if (p->c->corner_type_color_template[3][f])
      stbhw__draw_clipped_corner(p->data, p->stride, xpos, ypos, len, len*2, len+1, len*2+1);

   stbhw__set_pixel(p->data, p->stride, xpos, ypos, stbhw__corner_colors[0][a]);
   stbhw__set_pixel(p->data, p->stride, xpos, ypos+len, stbhw__corner_colors[3][b]);
   stbhw__set_pixel(p->data, p->stride, xpos, ypos+len*2+1, stbhw__corner_colors[2][c]);
   stbhw__set_pixel(p->data, p->stride, xpos+len+1, ypos, stbhw__corner_colors[1][d]);
   stbhw__set_pixel(p->data, p->stride, xpos+len+1, ypos+len, stbhw__corner_colors[0][e]);
   stbhw__set_pixel(p->data, p->stride, xpos+len+1, ypos+len*2+1, stbhw__corner_colors[3][f]);
}