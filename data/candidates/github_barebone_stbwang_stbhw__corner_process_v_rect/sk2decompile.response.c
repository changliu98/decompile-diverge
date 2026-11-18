static void stbhw__corner_process_v_rect(stbhw__rect_context *c, int x, int y,
                                         int a, int b, int c, int d, int e,
                                         int f) {
  int s = c->info->subdivide;
  stbhw__draw_hline(c->output, c->stride, x + 1, y, stbhw__v_line_colors[a * 4 + d],
                    s, 0);
  stbhw__draw_vline(c->output, c->stride, x, y + 1,
                    stbhw__v_line_colors[a * 4 + b], s, 5);
  stbhw__draw_vline(c->output, c->stride, x + s + 1, y + 1,
                    stbhw__v_line_colors[d * 4 + e], s, 1);
  stbhw__draw_vline(c->output, c->stride, x, y + s + 1,
                    stbhw__v_line_colors[b * 4 + c], s, 4);
  stbhw__draw_vline(c->output, c->stride, x + s + 1, y + s + 1,
                    stbhw__v_line_colors[e * 4 + f], s, 5);
  stbhw__draw_hline(c->output, c->stride, x + 1, y + s * 2 + 1,
                    stbhw__v_line_colors[c * 4 + f], s, 3);
  if (c->info->corner_mask[0][a])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, 1, 1);
  if (c->info->corner_mask[3][b])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, 1, s + 1);
  if (c->info->corner_mask[2][c])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, 1, s * 2 + 1);
  if (c->info->corner_mask[1][d])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, s + 1, 1);
  if (c->info->corner_mask[0][e])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, s + 1,
                               s + 1);
  if (c->info->corner_mask[3][f])
    stbhw__draw_clipped_corner(c->output, c->stride, x, y, s, s * 2, s + 1,
                               s * 2 + 1);
  stbhw__set_pixel(c->output, c->stride, x, y, &stbhw__v_colors[a * 3]);
  stbhw__set_pixel(c->output, c->stride, x, y + s, &stbhw__v_colors[b * 3 + 9]);
  stbhw__set_pixel(c->output, c->stride, x, y + s * 2 + 1,
                   &stbhw__v_colors[c * 3 + 6]);
  stbhw__set_pixel(c->output, c->stride, x + s + 1, y, &stbhw__v_colors[d * 3 + 3]);
  stbhw__set_pixel(c->output, c->stride, x + s + 1, y + s, &stbhw__v_colors[e * 3]);
  stbhw__set_pixel(c->output, c->stride, x + s + 1, y + s * 2 + 1,
                   &stbhw__v_colors[f * 3 + 9]);
}