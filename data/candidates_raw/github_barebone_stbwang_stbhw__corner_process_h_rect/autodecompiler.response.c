void stbhw__draw_box(stbhw_render_state *rs, int x0, int y0, int x1, int y1, int x2, int y2)
{
   int size = rs->style->size;

   stbhw__draw_hline(rs->dest, rs->stride, x0+1,y0, stbhw__corner_colors_to_edge_color[x1*4+y1], size, 2);
   stbhw__draw_hline(rs->dest, rs->stride, x0+1+size,y0, stbhw__corner_colors_to_edge_color[y1*4+y2], size, 3);
   stbhw__draw_vline(rs->dest, rs->stride, x0,y0+1, stbhw__corner_colors_to_edge_color[x1*4+x2], size, 1);
   stbhw__draw_vline(rs->dest, rs->stride, x0+1+size*2,y0+1, stbhw__corner_colors_to_edge_color[y2*4+x0], size, 4);

   stbhw__draw_hline(rs->dest, rs->stride, x0+1,y0+1+size, stbhw__corner_colors_to_edge_color[x2*4+y0], size, 0);
   stbhw__draw_hline(rs->dest, rs->stride, x0+1+size,y0+1+size, stbhw__corner_colors_to_edge_color[y0*4+x1], size, 2);

   if (rs->style->corners[14]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, 1, 1);
   if (rs->style->corners[18]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, size+1, 1);
   if (rs->style->corners[22]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, size*2+1, 1);
   if (rs->style->corners[10]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, 1, size+1);
   if (rs->style->corners[15]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, size+1, size+1);
   if (rs->style->corners[20]) stbhw__draw_clipped_corner(rs->dest, rs->stride, x0,y0, size*2, size, size*2+1, size+1);

   stbhw__set_pixel(rs->dest, rs->stride, x0,y0, &stbhw__corner_colors[3*x1+1]);
   stbhw__set_pixel(rs->dest, rs->stride, x0+size,y0, &stbhw__corner_colors[3*y1+2]);
   stbhw__set_pixel(rs->dest, rs->stride, x0+size*2+1,y0, &stbhw__corner_colors[3*y2+3]);

   stbhw__set_pixel(rs->dest, rs->stride, x0,y0+size+1, &stbhw__corner_colors[3*x2+0]);
   stbhw__set_pixel(rs->dest, rs->stride, x0+size,y0+size+1, &stbhw__corner_colors[3*y0+1]);
   stbhw__set_pixel(rs->dest, rs->stride, x0+size*2+1,y0+size+1, &stbhw__corner_colors[3*y1+2]);
}