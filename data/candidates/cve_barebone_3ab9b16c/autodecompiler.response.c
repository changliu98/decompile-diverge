void sycc420_to_rgb(struct fb_image *img)
{
 unsigned int bits_per_pixel = img->u.yuv420p[1].bits_per_pixel;
 unsigned int half_bits_per_pixel = 1 << (bits_per_pixel-1);
 unsigned int mask = (1 << bits_per_pixel) - 1;
 unsigned int width = img->u.yuv420p[0].width;
 unsigned int height = img->u.yuv420p[0].height;
 unsigned int pixels = width * height;
 unsigned int *y, *y2, *cb, *cr, *r, *g, *b, *r0, *g0, *b0;
 unsigned int i, j;

 y = img->u.yuv420p[0].data;
 cb = img->u.yuv420p[1].data;
 cr = img->u.yuv420p[2].data;

 r = r0 = malloc(pixels * sizeof(unsigned int));
 g = g0 = malloc(pixels * sizeof(unsigned int));
 b = b0 = malloc(pixels * sizeof(unsigned int));

 if (!r || !g || !b)
  goto fails;

 for (j = 0; j < height; j += 2) {
  if (j < (height & ~1)) {
   y2 = y + width;
   r = r0 + width;
   g = g0 + width;
   b = b0 + width;

   for (i = 0; i < width; i += 2) {
    sycc_to_rgb(half_bits_per_pixel, mask,
     *y, *cb, *cr, r, g, b);

    y++;
    r++;
    g++;
    b++;

    sycc_to_rgb(half_bits_per_pixel, mask,
     *y, *cb, *cr, r, g, b);

    y++;
    r++;
    g++;
    b++;

    sycc_to_rgb(half_bits_per_pixel, mask,
     *y2, *cb, *cr, r, g, b);

    y2++;
    r++;
    g++;
    b++;

    sycc_to_rgb(half_bits_per_pixel, mask,
     *y2, *cb, *cr, r, g, b);

    y2++;
    r++;
    g++;
    b++;

    cb++;
    cr++;
   }

   if (i < width) {
    sycc_to_rgb(half_bits_per_pixel, mask,
     *y, *cb, *cr, r, g, b);

    y++;
    r++;
    g++;
    b++;

    sycc_to_rgb(half_bits_per_pixel, mask,
     *y2, *cb, *cr, r, g, b);

    y2++;
    r++;
    g++;
    b++;

    cb++;
    cr++;
   }
   y += width;
   r += width;
   g += width;
   b += width;
  } else {
   for (i = 0; i < width; i += 2) {
    sycc_to_rgb(half_bits_per_pixel, mask,
     *y, *cb, *cr, r, g, b);

    y++;
    r++;
    g++;
    b++;

    sycc_to_rgb(half_bits_per_pixel, mask,
     *y, *cb, *cr, r, g, b);

    y++;
    r++;
    g++;
    b++;

    cb++;
    cr++;
   }
  }
 }

 free(img->u.yuv420p[0].data);
 img->u.yuv420p[0].data = r0;
 free(img->u.yuv420p[1].data);
 img->u.yuv420p[1].data = g0;
 free(img->u.yuv420p[2].data);
 img->u.yuv420p[2].data = b0;

 img->u.rgb24.width = width;
 img->u.rgb24.height = height;
 img->u.rgb24.xres = width;
 img->u.rgb24.yres = height;
 img->u.rgb24.bits_per_pixel = img->bits_per_pixel;
 img->u.rgb24.xres_virtual = img->bits_per_pixel;
 img->u.rgb24.yres_virtual = img->line_length;
 img->u.rgb24.line_length = img->line_length;

 return;

fails:
 if (r)
  free(r);
 if (g)
  free(g);
 if (b)
  free(b);
}