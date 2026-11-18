const char *__cdecl func0(const char *numbers)
{
  int v1; // eax
  bool v3; // [rsp+9h] [rbp-97h]
  char current[6]; // [rsp+Ah] [rbp-96h] BYREF
  int k; // [rsp+10h] [rbp-90h]
  int j; // [rsp+14h] [rbp-8Ch]
  int i; // [rsp+18h] [rbp-88h]
  int index; // [rsp+1Ch] [rbp-84h]
  const char *numto[10]; // [rsp+20h] [rbp-80h] BYREF
  int count[10]; // [rsp+70h] [rbp-30h] BYREF
  const char *numbersa; // [rsp+98h] [rbp-8h]

  numbersa = numbers;
  memset(count, 0, sizeof(count));
  memcpy(numto, &off_3D90, sizeof(numto));
  index = 0;
  if ( *numbersa )
  {
    do
    {
      for ( i = 0; ; ++i )
      {
        v3 = 0;
        if ( numbersa[i] != 32 )
          v3 = numbersa[i] != 0;
        if ( !v3 )
          break;
        current[i] = numbersa[i];
      }
      current[i] = 0;
      for ( j = 0; j < 10; ++j )
      {
        if ( !strcmp(current, numto[j]) )
        {
          ++count[j];
          break;
        }
      }
      numbersa += i + 1;
    }
    while ( *(numbersa - 1) );
  }
  for ( i = 0; i < 10; ++i )
  {
    for ( j = 0; j < count[i]; ++j )
    {
      for ( k = 0; numto[i][k]; func0_out[index++] = numto[i][k++] )
        ;
      v1 = index++;
      func0_out[v1] = 32;
    }
  }
  if ( index <= 0 )
    func0_out[0] = 0;
  else
    func0_out[index - 1] = 0;
  return func0_out;
}