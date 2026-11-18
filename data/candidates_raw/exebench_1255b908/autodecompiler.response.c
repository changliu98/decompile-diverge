static int
adjust_width(int *w, int *x, int min_w, int max_w)
{
 int ret;

 if (*w < min_w) {
  int diff = min_w - *w;
  *x += *w;
  *w = min_w;
  ret = diff;
 } else if (*w + *x >= max_w) {
  *x = max_w - *w;
 } else {
  ret = 0;
 }

 while (ret > 0) {
  ret = 0;
 }
 return ret;
}