void short_to_xy(short s, int *x, int *y)
{
 *x = ((s & 0xff) - 2);
 *y = (((s >> 8) & 0xff) - 2);
}