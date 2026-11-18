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
  unsigned char *data = p->data;
  int stride = p->stride;
  stbhw_config *config = p->c;
  int len = config->short_side_len;

  // Draw edges
  stbhw__draw_hline(data, stride, xpos + 1, ypos, stbhw__corner_colors_to_edge_color[4 * a + d], len, 0);
  stbhw__draw_vline(data, stride, xpos, ypos + 1, stbhw__corner_colors_to_edge_color[4 * a + b], len, 5);
  stbhw__draw_vline(data, stride, len + xpos + 1, ypos + 1, stbhw__corner_colors_to_edge_color[4 * d + e], len, 1);
  stbhw__draw_vline(data, stride, xpos, len + ypos + 1, stbhw__corner_colors_to_edge_color[4 * b + c], len, 4);
  stbhw__draw_vline(data, stride, len + xpos + 1, len + ypos + 1, stbhw__corner_colors_to_edge_color[4 * e + f], len, 5);
  stbhw__draw_hline(data, stride, xpos + 1, 2 * len + ypos + 1, stbhw__corner_colors_to_edge_color[4 * c + f], len, 3);

  // Draw clipped corners based on color templates
  if (config->corner_type_color_template[0][a])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, 1, 1);
  if (config->corner_type_color_template[3][b])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, 1, len + 1);
  if (config->corner_type_color_template[2][c])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, 1, 2 * len + 1);
  if (config->corner_type_color_template[1][d])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, len + 1, 1);
  if (config->corner_type_color_template[0][e])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, len + 1, len + 1);
  if (config->corner_type_color_template[3][f])
    stbhw__draw_clipped_corner(data, stride, xpos, ypos, len, 2 * len, len + 1, 2 * len + 1);

  // Draw corner pixels
  // Note: Magic numbers (e.g., 36, 24, 12) likely represent byte offsets into a flattened 2D array
  stbhw__set_pixel(data, stride, xpos, ypos, &stbhw__corner_colors[3 * a]);
  stbhw__set_pixel(data, stride, xpos, len + ypos, &stbhw__corner_colors[3 * b + 36]);
  stbhw__set_pixel(data, stride, xpos, 2 * len + ypos + 1, &stbhw__corner_colors[3 * c + 24]);
  stbhw__set_pixel(data, stride, len + xpos + 1, ypos, &stbhw__corner_colors[3 * d + 12]);
  stbhw__set_pixel(data, stride, len + xpos + 1, len + ypos, &stbhw__corner_colors[3 * e]);
  stbhw__set_pixel(data, stride, len + xpos + 1, 2 * len + ypos + 1, &stbhw__corner_colors[3 * f + 36]);
}