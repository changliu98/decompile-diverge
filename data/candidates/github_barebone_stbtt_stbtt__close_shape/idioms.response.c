int stbtt__close_shape(struct stbtt_vertex *vertices, int num_vertices, int was_off, int start_off, int x, int y, int xoff, int yoff, int x1, int y1)
{
   int i;
   if (start_off)
   {
      if (was_off)
      {
         i = num_vertices++;
         stbtt__close_shape(&vertices[i], 3, (x + x1)>>1, (y + y1)>>1, x1, y1);
      }
      i = num_vertices++;
      stbtt__close_shape(&vertices[i], 3, x, y, xoff, yoff);
   }
   else
   {
      i = num_vertices++;
      if (was_off)
         stbtt__close_shape(&vertices[i], 3, x, y, x1, y1);
      else
         stbtt__close_shape(&vertices[i], 2, x, y, 0, 0);
   }
   return i;
}