void stbhw__draw_tile(struct stbhw__process *p, int xpos, int ypos, int a, int b, int c, int d, int e, int f)
{
  int len = p->c->short_side_len;
  int color;
  int i; int j;
  color = stbhw__corner_colors_to_edge_color[a][d];
  stbhw__draw_edge(p->data, p->stride, xpos + 1, ypos, color, len, 0);
  color = stbhw__corner_colors_to_edge_color[a][b];
  stbhw__draw_edge(p->data, p->stride, xpos, ypos + 1, color, len, 5);
  color = stbhw__corner_colors_to_edge_color[d][e];
  stbhw__draw_edge(p->data, p->stride, xpos + len + 1, ypos + 1, color, len, 1);
  color = stbhw__corner_colors_to_edge_color[b][c];
  stbhw__draw_edge(p->data, p->stride, xpos, ypos + len + 1, color, len, 4);
  color = stbhw__corner_colors_to_edge_color[e][f];
  stbhw__draw_edge(p->data, p->stride, xpos + len + 1, ypos + len + 1, color, len, 5);
  color = stbhw__corner_colors_to_edge_color[c][f];
  stbhw__draw_edge(p->data, p->stride, xpos + 1, ypos + len * 2 + 1, color, len, 3);
  if (p->c->corner_type_color_template[0][a])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, 1, 1);
  if (p->c->corner_type_color_template[3][b])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, 1, len + 1);
  if (p->c->corner_type_color_template[2][c])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, 1, len * 2 + 1);
  if (p->c->corner_type_color_template[1][d])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, len + 1, 1);
  if (p->c->corner_type_color_template[0][e])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, len + 1, len + 1);
  if (p->c->corner_type_color_template[3][f])
    stbhw__draw_color(p->data, p->stride, xpos, ypos, len, len * 2, len + 1, len * 2 + 1);
  stbhw__draw_corner(p->data, p->stride, xpos, ypos, stbhw__corner_colors[a]);
  stbhw__draw_corner(p->data, p->stride, xpos, ypos + len, stbhw__corner_colors[b + 36]);
  stbhw__draw_corner(p->data, p->stride, xpos, ypos + len * 2 + 1, stbhw__corner_colors[c + 24]);
  stbhw__draw_corner(p->data, p->stride, xpos + len + 1, ypos, stbhw__corner_colors[d + 12]);
  stbhw__draw_corner(p->data, p->stride, xpos + len + 1, ypos + len, stbhw__corner_colors[e]);
  stbhw__draw_corner(p->data, p->stride, xpos + len + 1, ypos + len * 2 + 1, stbhw__corner_colors[f + 36]);
}