char *__cdecl func0(int *test_tup, int size)
{
  int i_0; // [rsp+Ch] [rbp-384h]
  char buffer[50]; // [rsp+10h] [rbp-380h] BYREF
  char *result; // [rsp+48h] [rbp-348h]
  int j; // [rsp+50h] [rbp-340h]
  int found; // [rsp+54h] [rbp-33Ch]
  int i; // [rsp+58h] [rbp-338h]
  int count; // [rsp+5Ch] [rbp-334h]
  dict freq[100]; // [rsp+60h] [rbp-330h]
  int sizea; // [rsp+384h] [rbp-Ch]
  int *test_tupa; // [rsp+388h] [rbp-8h]

  test_tupa = test_tup;
  sizea = size;
  count = 0;
  for ( i = 0; i < sizea; ++i )
  {
    found = 0;
    for ( j = 0; j < count; ++j )
    {
      if ( freq[j].key == test_tupa[i] )
      {
        ++freq[j].value;
        found = 1;
        break;
      }
    }
    if ( !found )
    {
      freq[count].key = test_tupa[i];
      freq[count++].value = 1;
    }
  }
  result = (char *)malloc(0x3E8uLL);
  *result = 0;
  strcat(result, "{");
  for ( i_0 = 0; i_0 < count; ++i_0 )
  {
    sprintf(buffer, "%d: %d", (unsigned int)freq[i_0].key, (unsigned int)freq[i_0].value);
    strcat(result, buffer);
    if ( i_0 < count - 1 )
      strcat(result, ", ");
  }
  strcat(result, "}");
  return result;
}