int cp_unfilter(int w, int h, int bpp, unsigned char *raw)
{
 int y, x, stride = w * bpp;
 unsigned char *prev, *curr;

 curr = raw;


 if (h > 0) {
  unsigned char *init = curr;
  curr++;

  switch (*init) {
  case 1:
   for (x = bpp; x < stride; x++)
    curr[x] += curr[x - bpp];
   break;
  case 2:
   break;
  case 3:
   for (x = bpp; x < stride; x++)
    curr[x] += curr[x - bpp] / 2;
   break;
  case 4:
   for (x = bpp; x < stride; x++)
    curr[x] += cp_paeth(curr[x - bpp], 0, 0);
   break;
  default:
   return 0;
  }
 }

 prev = curr;
 curr += stride;


 for (y = 1; y < h; y++) {
  unsigned char *init = curr;
  curr++;

  switch (*init) {
  case 1:
   for (x = 0; x < bpp; x++)
    curr[x] = curr[x];
   for (; x < stride; x++)
    curr[x] += curr[x - bpp];
   break;
  case 2:
   for (x = 0; x < bpp; x++)
    curr[x] += prev[x];
   for (; x < stride; x++)
    curr[x] += prev[x];
   break;
  case 3:
   for (x = 0; x < bpp; x++)
    curr[x] += prev[x] / 2;
   for (; x < stride; x++)
    curr[x] += (prev[x] + curr[x - bpp]) / 2;
   break;
  case 4:
   for (x = 0; x < bpp; x++)
    curr[x] += prev[x];
   for (; x < stride; x++)
    curr[x] += cp_paeth(curr[x - bpp], prev[x], prev[x - bpp]);
   break;
  default:
   return 0;
  }

  prev = curr;
  curr += stride;
 }

 return 1;
}