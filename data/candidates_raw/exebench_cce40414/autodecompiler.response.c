int plot_digit_wierd(char c, float x, float y, float h, float w,
       float *px, float *py)
{
 int i, n, l, ll, le, st, lb, ie, ib;
 float cs, rs, he, hl;

 n = 0;
 switch(c) {
 case '0':
 case '1':
 case '2':
 case '3':
 case '4':
 case '5':
 case '6':
 case '7':
 case '8':
 case '9':
  i = c - '0';
  ib = plot_digit_wierd_lt[i+1];
  ie = plot_digit_wierd_lt[i+2] - 1;
  for (i = ib; i <= ie; i++) {
   ll = plot_digit_wierd_lb[i] / 10;
   le = plot_digit_wierd_lb[i] - 10 * ll;
   hl = h * ll;
   he = w * le;
   if (i != ib) {
    px[n] = rs;
    py[n] = cs;
    n++;
    px[n] = x - hl;
    py[n] = y - he;
    n++;
   }
   rs = x - hl;
   cs = y - he;
  }
  l = n;
  break;
 default:
  l = 0;
  break;
 }
 return l;
}