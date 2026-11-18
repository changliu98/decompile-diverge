char *__cdecl func0(int n, int m)
{
  int v2; // ecx
  int index; // [rsp+Ch] [rbp-24h]
  char *out; // [rsp+10h] [rbp-20h]
  int num; // [rsp+1Ch] [rbp-14h]

  if ( n > m )
    return (char *)&unk_2004;
  num = (n + m) / 2;
  out = (char *)malloc(0x21uLL);
  *out = 0;
  index = 31;
  out[32] = 0;
  do
  {
    v2 = index--;
    out[v2] = num % 2 + 48;
    num /= 2;
  }
  while ( num > 0 );
  return &out[index + 1];
}