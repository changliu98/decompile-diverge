void stbi_write_jpg(char *filename, int x, int y, int comp, const void *data, int quality)
{
   unsigned char *out;
   unsigned char *xform[3];
   int rgb[3];

   int i;
   int n = (comp & 1) ? 1 : 3;

   out = (unsigned char *) stbi_zlib_compress((char *) data, x*y*comp, &n, 80);

   if (!out) return;

   rgb[0] = rgb[1] = rgb[2] = 0;
   if (comp & 1) rgb[0] = rgb[1] = rgb[2] = 1;

   for (i=0; i < 3; ++i) {
      int w = x;
      int h = y;
      if (n == 1) {
         w = (w + 1)/2;
         h = (h + 1)/2;
      }
      xform[i] = (unsigned char *) stbi_zlib_compress((char *) data + i, w*h*comp, &n, 50);
      if (!xform[i]) {
         free(out);
         return;
      }
   }

   stbi__write_jpgf(out,n,x,y,comp,rgb,xform[0],xform[1],xform[2]);
   free(out);
   free(xform[0]);
   free(xform[1]);
   free(xform[2]);
}