int cp_unfilter(int w, int h, int bpp, unsigned char *data)
{
 int y, x, bpl = w * bpp, f;
 unsigned char *line, *prev;

 if (h > 0) {
  line = data;
  switch (*line++) {
  case 0:
   break;
  case 1:
   for (x = bpp; x < bpl; x++)
    line[x] += line[x - bpp];
   break;
  case 2:
   break;
  case 3:
   for (x = bpp; x < bpl; x++)
    line[x] += line[x - bpp] / 2;
   break;
  case 4:
   for (x = bpp; x < bpl; x++)
    line[x] += cp_paeth(line[x - bpp], 0, 0);
   break;
  default:
   return 0;
  }
 }

 prev = line;
 line += bpl;

 for (y = 1; y < h; y++) {
  switch (*line++) {
  case 0:
   break;
  case 1:
   for (x = 0; x < bpp; x++)
    line[x] += 0;
   for (; x < bpl; x++)
    line[x] += line[x - bpp];
   break;
  case 2:
   for (x = 0; x < bpp; x++)
    line[x] += prev[x];
   for (; x < bpl; x++)
    line[x] += line[x - bpp];
   break;
  case 3:
   for (x = 0; x < bpp; x++)
    line[x] += prev[x] / 2;
   for (; x < bpl; x++)
    line[x] += (line[x - bpp] + prev[x]) / 2;
   break;
  case 4:
   for (x = 0; x < bpp; x++)
    line[x] += prev[x];
   for (; x < bpl; x++)
    line[x] += cp_paeth(line[x - bpp], prev[x], prev[x - bpp]);
   break;
  default:
   return 0;
  }
  prev = line;
  line += bpl;
 }

 return 1;
}