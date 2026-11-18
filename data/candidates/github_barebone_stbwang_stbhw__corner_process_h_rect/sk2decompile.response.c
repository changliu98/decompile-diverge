static void stbhw__corner_process_h_rect(stbhw__rect_pack_node *node, int x,
                                         int y, int a, int b, int c, int d,
                                         int e, int f) {
  int s = node->parent->size;
  stbhw__draw_hline(node->image, node->pixels_per_row, x + 1, y,
                    stbhw__corner_h_table[a * 4 + b], s, 2);
  stbhw__draw_hline(node->image, node->pixels_per_row, x + 1 + s, y,
                    stbhw__corner_h_table[b * 4 + c], s, 3);
  stbhw__draw_vline(node->image, node->pixels_per_row, x, y + 1,
                    stbhw__corner_h_table[a * 4 + d], s, 1);
  stbhw__draw_vline(node->image, node->pixels_per_row, x + 1 + s * 2, y + 1,
                    stbhw__corner_h_table[c * 4 + f], s, 4);
  stbhw__draw_hline(node->image, node->pixels_per_row, x + 1, y + 1 + s,
                    stbhw__corner_h_table[d * 4 + e], s, 0);
  stbhw__draw_hline(node->image, node->pixels_per_row, x + 1 + s, y + 1 + s,
                    stbhw__corner_h_table[e * 4 + f], s, 2);
  if (node->parent->used[1][a])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, 1, 1);
  if (node->parent->used[2][b])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, s + 1, 1);
  if (node->parent->used[3][c])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, 2 * s + 1, 1);
  if (node->parent->used[0][d])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, 1, s + 1);
  if (node->parent->used[1][e])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, s + 1, s + 1);
  if (node->parent->used[2][f])
    stbhw__draw_clipped_corner(node->image, node->pixels_per_row, x, y, 2 * s,
                               s, 2 * s + 1, s + 1);
  stbhw__set_pixel(node->image, node->pixels_per_row, x, y,
                   &stbhw__color_table[a * 3 + 3]);
  stbhw__set_pixel(node->image, node->pixels_per_row, x + s, y,
                   &stbhw__color_table[b * 3 + 6]);
  stbhw__set_pixel(node->image, node->pixels_per_row, x + s * 2 + 1, y,
                   &stbhw__color_table[c * 3 + 9]);
  stbhw__set_pixel(node->image, node->pixels_per_row, x, y + s,
                   &stbhw__color_table[d * 3 + 0]);
  stbhw__set_pixel(node->image, node->pixels_per_row, x + s, y + s,
                   &stbhw__color_table[e * 3 + 3]);
  stbhw__set_pixel(node->image, node->pixels_per_row, x + s * 2 + 1, y + s,
                   &stbhw__color_table[f * 3 + 6]);
}