void stbhw__draw_tile(struct stbhw__process *p, int xpos, int ypos, int a, int b, int c, int d, int e, int f)
{
  int len = p->c->short_side_len;
  int color;
  int x; int y;
  color = stbhw__corner_colors_to_edge_color[a * 4 + b];
  x = xpos + 1;
  y = ypos;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 2);
  color = stbhw__corner_colors_to_edge_color[b * 4 + c];
  x = xpos + len + 1;
  y = ypos;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 3);
  color = stbhw__corner_colors_to_edge_color[a * 4 + d];
  x = xpos;
  y = ypos + 1;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 1);
  color = stbhw__corner_colors_to_edge_color[c * 4 + f];
  x = xpos + len + 1;
  y = ypos + 1;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 4);
  color = stbhw__corner_colors_to_edge_color[d * 4 + e];
  x = xpos + 1;
  y = ypos + len + 1;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 0);
  color = stbhw__corner_colors_to_edge_color[e * 4 + f];
  x = xpos + len + 1;
  y = ypos + len + 1;
  stbhw__draw_edge(p->data, p->stride, x, y, color, len, 2);
  if (p->c->corner_type_color_template[1][a])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, 1, 1);
  if (p->c->corner_type_color_template[2][b])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, len + 1, 1);
  if (p->c->corner_type_color_template[3][c])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, len * 2 + 1, 1);
  if (p->c->corner_type_color_template[0][d])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, 1, len + 1);
  if (p->c->corner_type_color_template[1][e])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, len + 1, len + 1);
  if (p->c->corner_type_color_template[2][f])
    stbhw__draw_corner(p->data, p->stride, xpos, ypos, len * 2, len, len * 2 + 1, len + 1);
  stbhw__draw_tile_center(p->data, p->stride, xpos, ypos, stbhw__corner_colors[a * 4 + 1]);
  stbhw__draw_tile_center(p->data, p->stride, xpos + len, ypos, stbhw__corner_colors[b * 4 + 2]);
  stbhw__draw_tile_center(p->data, p->stride, xpos + len * 2 + 1, ypos, stbhw__corner_colors[c * 4 + 3]);
  stbhw__draw_tile_center(p->data, p->stride, xpos, ypos + len + 1, stbhw__corner_colors[d * 4 + 0]);
  stbhw__draw_tile_center(p->data, p->stride, xpos + len, ypos + len + 1, stbhw__corner_colors[e * 4 + 1]);
  stbhw__draw_tile_center(p->data, p->stride, xpos + len * 2 + 1, ypos + len + 1, stbhw__corner_colors[f * 4 + 2]);
}