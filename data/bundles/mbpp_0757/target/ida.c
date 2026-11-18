char *__cdecl func0(char **test_list, int size)
{
  int i; // [rsp+8h] [rbp-88h]
  int len; // [rsp+Ch] [rbp-84h]
  char reversed[100]; // [rsp+10h] [rbp-80h] BYREF
  int idxn; // [rsp+78h] [rbp-18h]
  int idx; // [rsp+7Ch] [rbp-14h]
  int count; // [rsp+80h] [rbp-10h]
  int sizea; // [rsp+84h] [rbp-Ch]
  char **test_lista; // [rsp+88h] [rbp-8h]

  test_lista = test_list;
  sizea = size;
  count = 0;
  for ( idx = 0; idx < sizea; ++idx )
  {
    for ( idxn = idx; idxn < sizea; ++idxn )
    {
      len = strlen(test_lista[idx]);
      for ( i = 0; i < len; ++i )
        reversed[i] = test_lista[idx][len - 1 - i];
      reversed[len] = 0;
      if ( !strcmp(test_lista[idxn], reversed) )
        ++count;
    }
  }
  sprintf(func0_result, "%d", (unsigned int)count);
  return func0_result;
}