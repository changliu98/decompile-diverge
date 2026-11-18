void quicktake_100_load_raw()
{
  unsigned char pixel[1280 +4][1600 +4];
  int row, col, rb, sharp, s;
  int g, r;

  getbithuff(-1, NULL);
  memset (pixel, 128, (1280 +4)*(1600 +4));
  for (row=2; row < height+2; row++)
    for (col=2 +(row&1); col < width+2; col+=2) {
      g = (pixel[row-1][col-1] + pixel[row-1][col+1] + pixel[row][col] + 2) >> 2;
      g = g + quicktake_100_load_raw::gstep[getbithuff(4, NULL)];
      g = (g > 255 ? 255 : (g < 0 ? 0 : g));
      pixel[row][col] = g;
      if (col < 4) pixel[row+1][2-(row&1) ] = pixel[row][col] = g;
      if (row == 2) pixel[1][col+3] = pixel[1][col+1] = g;
    }
  pixel[row][col] = g;
  for (rb=0; rb < 2; rb++)
    for (row=2 +rb; row < height+2; row+=2)
      for (col=2 +(1-(row&1)); col < width+2; col+=2) {
 if (row < 4 || col < 4)
   sharp = 2;
 else {
   s = abs(pixel[row][col] - pixel[row-2][col])
     + abs(pixel[row][col] - pixel[row][col-2])
     + abs(pixel[row-2][col-2] - pixel[row][col-2])
     + abs(pixel[row-2][col] - pixel[row-2][col-2]);
   sharp = s < 4 ? 0 : s < 8 ? 1 : s < 16 ? 2 : s < 32 ? 3 : s < 48 ? 4 : 5;
 }
 r = (pixel[row][col] + pixel[row-2][col] + 1) >> 1;
 r = r + quicktake_100_load_raw::rstep[sharp][getbithuff(2, NULL)];
 r = (r > 255 ? 255 : (r < 0 ? 0 : r));
 pixel[row][col] = r;
 if (row < 4) pixel[row-2][col+2] = r;
 if (col < 4) pixel[row+4][col-2] = r;
      }
  for (row=2; row < height+2; row++)
    for (col=2 +(1-(row&1)); col < width+2; col+=2) {
      g = (pixel[row][col-1] + pixel[row][col] + pixel[row][col+1] + 1) >> 1;
      g = g - 256;
      g = (g > 255 ? 255 : (g < 0 ? 0 : g));
      pixel[row][col] = g;
    }
  for (row=0; row < height; row++)
    for (col=0; col < width; col++)
      raw_image[row*raw_width + col] = quicktake_100_load_raw::t_curve[pixel[row+2][col+2]];
  maximum = 1023;
}