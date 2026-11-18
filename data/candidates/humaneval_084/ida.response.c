char *__cdecl func0(int N)
{
  int v1; // ecx
  char temp; // [rsp+7h] [rbp-29h]
  int i_0; // [rsp+8h] [rbp-28h]
  int index; // [rsp+Ch] [rbp-24h]
  char *bi; // [rsp+10h] [rbp-20h]
  int i; // [rsp+1Ch] [rbp-14h]
  int sum; // [rsp+20h] [rbp-10h]
  char str[6]; // [rsp+26h] [rbp-Ah] BYREF
  int Na; // [rsp+2Ch] [rbp-4h]

  Na = N;
  sprintf(str, "%d", (unsigned int)N);
  sum = 0;
  for ( i = 0; str[i]; ++i )
    sum += str[i] - 48;
  bi = (char *)malloc(0x21uLL);
  index = 0;
  if ( sum )
  {
    while ( sum > 0 )
    {
      v1 = index++;
      bi[v1] = sum % 2 + 48;
      sum /= 2;
    }
  }
  else
  {
    index = 1;
    *bi = 48;
  }
  bi[index] = 0;
  for ( i_0 = 0; i_0 < index / 2; ++i_0 )
  {
    temp = bi[i_0];
    bi[i_0] = bi[index - i_0 - 1];
    bi[index - i_0 - 1] = temp;
  }
  return bi;
}