void decode_dir(short d, int *x, int *y)
{
 *x = (d & 0xff) - 2;
 *y = ((d & 0xff00) >> 8) - 2;
}