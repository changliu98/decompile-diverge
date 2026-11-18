void cross_product(int x1, int y1, int x2, int y2, int *x3, int *y3)
{
 *x3 = x1*y2 + x2*y1;
 *y3 = y1*y2;
}