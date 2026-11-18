char *__cdecl func0(char **test_list, int size)
{
  double v2; // xmm0_8
  double first; // [rsp+8h] [rbp-88h]
  char temp[100]; // [rsp+10h] [rbp-80h] BYREF
  int i; // [rsp+80h] [rbp-10h]
  int sizea; // [rsp+84h] [rbp-Ch]
  char **test_lista; // [rsp+88h] [rbp-8h]

  test_lista = test_list;
  sizea = size;
  strcpy(func0_res, "[");
  for ( i = 0; i < sizea; i += 2 )
  {
    first = atof(test_lista[i]);
    v2 = atof(test_lista[i + 1]);
    snprintf(temp, 0x64uLL, "(%.2f, %.2f)", first, v2);
    strcat(func0_res, temp);
    if ( i < sizea - 2 )
      strcat(func0_res, ", ");
  }
  strcat(func0_res, "]");
  return func0_res;
}