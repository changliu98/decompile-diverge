void decode_dir(short d,int *x,int *y)
{
  *x = ((int)d & 0xffU) - 2;
  *y = ((int)d & 0xff00U) / 256 - 2;
}