char *__cdecl func0(char **test_tup, int size)
{
  int i; // [rsp+Ch] [rbp-14h]
  char delim[2]; // [rsp+12h] [rbp-Eh] BYREF
  int sizea; // [rsp+14h] [rbp-Ch]
  char **test_tupa; // [rsp+18h] [rbp-8h]

  test_tupa = test_tup;
  sizea = size;
  strcpy(func0_res, "");
  strcpy(delim, "-");
  for ( i = 0; i < sizea; ++i )
  {
    strcat(func0_res, test_tupa[i]);
    if ( i < sizea - 1 )
      strcat(func0_res, delim);
  }
  return func0_res;
}