static int get_color(int r, int g, int b, int max, int *diff)
{
 int avg;
 int ret;

 avg = (r + g + b) / 3;

 if (diff) {
  int d1, d2, d3, d4, d5, d6, d7, d8, d9;

  d1 = ((r - avg) > 0 ? (r - avg) : -((r - avg)));
  d2 = ((g - avg) > 0 ? (g - avg) : -((g - avg)));
  d3 = ((d1) > (d2) ? (d1) : (d2));
  d4 = ((b - avg) > 0 ? (b - avg) : -((b - avg)));
  d5 = ((d3) > (d4) ? (d3) : (d4));

  d6 = ((r - avg) > 0 ? (r - avg) : -((r - avg)));
  d7 = ((g - avg) > 0 ? (g - avg) : -((g - avg)));
  d8 = ((d6) > (d7) ? (d6) : (d7));
  d9 = ((b - avg) > 0 ? (b - avg) : -((b - avg)));

  *diff = ((d5) > (d9) ? (d5) : (d9));
 }

 if (r < max && g < max && b < max)
  ret = avg;
 else {
  ret = (avg > max ? avg : max);
 }

 return ret;
}