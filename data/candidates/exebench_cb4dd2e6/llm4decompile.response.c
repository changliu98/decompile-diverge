int RGB565toRGB32(unsigned char *dest_ptr, int dest_width, int dest_height, int dest_pitch, int dest_x, int dest_y, int dest_dx, int dest_dy, unsigned char *src_ptr, int src_width, int src_height, int src_pitch, int src_x, int src_y, int src_dx, int src_dy)
{







 int x, y;







 unsigned char *s;
 unsigned char *d;







 int d_width, d_height;







 int s_width, s_height;







 int s_x, s_y, d_x, d_y;







 int d_pitch, s_pitch;







 unsigned int r, g, b;







 unsigned short *src;
 unsigned int *dest;







 s_x = src_x;
 s_y = src_y;
 d_x = dest_x;
 d_y = dest_y;
 s_width = src_width;
 s_height = src_height;
 d_width = dest_width;
 d_height = dest_height;
 s_pitch = src_pitch;
 d_pitch = dest_pitch;







 src = (unsigned short *)src_ptr;
 dest = (unsigned int *)dest_ptr;







 for (y = 0; y < d_height; y++)
 {







  s = (unsigned char *)(src + (y + s_y) * s_pitch + s_x * 2);







  d = (unsigned char *)(dest + (y + d_y) * d_pitch + d_x * 4);







  for (x = 0; x < d_width; x++)
  {







   r = (((*s) & 0xF800) >> 11) << 3;







   g = (((*s) & 0x07E0) >> 5) << 2;







   b = (((*s) & 0x001F) >> 0) << 3;







   *((unsigned int *)d) = (unsigned int)(0xFF000000 | (r << 16) | (g << 8) | (b << 0));







   s += 2;







   d += 4;
  }
 }







 return -1;
}