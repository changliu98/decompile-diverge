char *__cdecl func0(int *test_tup, int size)
{
  double v3; // [rsp+8h] [rbp-28h]
  char *result_str; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]
  int res; // [rsp+20h] [rbp-10h]

  res = 0;
  for ( i = 0; i < size; ++i )
  {
    v3 = (double)test_tup[i];
    res = (int)(v3 * pow(2.0, (double)(size - 1 - i)) + (double)res);
  }
  result_str = (char *)malloc(0xCuLL);
  sprintf(result_str, "%d", (unsigned int)res);
  return result_str;
}