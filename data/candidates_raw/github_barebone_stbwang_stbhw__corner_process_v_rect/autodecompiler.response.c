void stbhw__draw_box(stbhw__box *box, int x0, int y0, int x1, int y1, int x2, int y2)
{
   int size = box->g[1];
   stbhw__draw_hline(box->buffer, box->stride, x0+1,y0 , stbhw__corner_colors_to_edge_color[x1*4+ x2], size);
   stbhw__draw_vline(box->buffer, box->stride, x0 ,y0+1, stbhw__corner_colors_to_edge_color[x1*4+ y1], size);
   stbhw__draw_vline(box->buffer, box->stride, x0+1+size,y0+1, stbhw__corner_colors_to_edge_color[x2*4+ y2], size);
   stbhw__draw_vline(box->buffer, box->stride, x0 ,y0+1+size, stbhw__corner_colors_to_edge_color[y1*4+ y2], size);
   stbhw__draw_vline(box->buffer, box->stride, x0+1+size,y0+1+size, stbhw__corner_colors_to_edge_color[y2*4+ x0], size);
   stbhw__draw_hline(box->buffer, box->stride, x0+1,y0+size+1, stbhw__corner_colors_to_edge_color[y2*4+ x0], size);

   if (box->g[10 +x1]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, 1, 1);
   if (box->g[22 +y1]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, 1, size+1);
   if (box->g[18 +y2]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, 1, size*2+1);
   if (box->g[14 +x2]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, size+1, 1);
   if (box->g[10 +y2]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, size+1, size+1);
   if (box->g[22 +x0]) stbhw__draw_clipped_corner(box->buffer, box->stride, x0 ,y0 , size, size, size+1, size*2+1);

   stbhw__set_pixel(box->buffer, box->stride, x0 ,y0 , &stbhw__corner_colors[3*x1+0]);
   stbhw__set_pixel(box->buffer, box->stride, x0 ,y0+size, &stbhw__corner_colors[3*y1+3]);
   stbhw__set_pixel(box->buffer, box->stride, x0 ,y0+size+1, &stbhw__corner_colors[3*y2+2]);
   stbhw__set_pixel(box->buffer, box->stride, x0+1+size,y0 , &stbhw__corner_colors[3*x2+1]);
   stbhw__set_pixel(box->buffer, box->stride, x0+1+size,y0+size, &stbhw__corner_colors[3*y2+0]);
   stbhw__set_pixel(box->buffer, box->stride, x0+1+size,y0+size+1, &stbhw__corner_colors[3*x0+3]);
}