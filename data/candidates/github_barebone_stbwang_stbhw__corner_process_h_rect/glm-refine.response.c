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
    // Cache frequently accessed pointers and values
    void *data             = p->data;
    int   stride           = p->stride;
    int   len              = p->c->short_side_len;
    int  *color_template   = p->c->corner_type_color_template[0]; // Base pointer for 2D array

    // Draw horizontal edges
    stbhw__draw_hline(data, stride, xpos + 1,         ypos,             EDGE_COLOR(a, b), len, 2);
    stbhw__draw_hline(data, stride, len + xpos + 1,   ypos,             EDGE_COLOR(b, c), len, 3);
    stbhw__draw_hline(data, stride, xpos + 1,         len + ypos + 1,   EDGE_COLOR(d, e), len, 0);
    stbhw__draw_hline(data, stride, len + xpos + 1,   len + ypos + 1,   EDGE_COLOR(e, f), len, 2);

    // Draw vertical edges
    stbhw__draw_vline(data, stride, xpos,             ypos + 1,         EDGE_COLOR(a, d), len, 1);
    stbhw__draw_vline(data, stride, 2 * len + xpos + 1, ypos + 1,       EDGE_COLOR(c, f), len, 4);

    // Draw clipped corners based on the color template
    // Note: color_template[1][a] translates to (color_template + 4)[a] which is color_template[4 + a]
    if (color_template[4 + a]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, 1,             1);
    if (color_template[8 + b]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, len + 1,       1);
    if (color_template[12 + c]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, 2 * len + 1,  1);
    if (color_template[0 + d]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, 1,             len + 1);
    if (color_template[4 + e]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, len + 1,       len + 1);
    if (color_template[8 + f]) stbhw__draw_clipped_corner(data, stride, xpos, ypos, 2 * len, len, 2 * len + 1,  len + 1);

    // Draw corner pixels
    stbhw__set_pixel(data, stride, xpos,               ypos,             &stbhw__corner_colors[3 * a + 12]);
    stbhw__set_pixel(data, stride, len + xpos,         ypos,             &stbhw__corner_colors[3 * b + 24]);
    stbhw__set_pixel(data, stride, 2 * len + xpos + 1, ypos,             &stbhw__corner_colors[3 * c + 36]);
    stbhw__set_pixel(data, stride, xpos,               len + ypos + 1,   &stbhw__corner_colors[3 * d     ]);
    stbhw__set_pixel(data, stride, len + xpos,         len + ypos + 1,   &stbhw__corner_colors[3 * e + 12]);
    stbhw__set_pixel(data, stride, 2 * len + xpos + 1, len + ypos + 1,   &stbhw__corner_colors[3 * f + 24]);
}