void easterg(int y, int *m, int *d)
{
 int a,b,c,f,g,h,i,k,l,m1,n,p;

 a = y % 19;
 b = y / 100;
 c = y % 100;
 f = (13 + 8 * b) / 25;
 g = b / 4;
 h = (19 * a + b - g - f + 15) % 30;
 i = c / 4;
 k = c % 4;
 l = (32 + 2 * g + 2 * i - h - k) % 7;
 m1 = (a + 11 * h + 22 * l) / 451;
 n = h + l - 7 * m1 + 114;
 *m = n / 31;
 *d = (n % 31) + 1;
}