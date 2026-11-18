void __cdecl decode_dir(short d, int *x, int *y)
{
  *x = (unsigned __int8)d - 2;
  *y = ((d & 0xFF00) >> 8) - 2;
}