char *__cdecl func0(int a, int b, int c, int d)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int i_2; // [rsp+Ch] [rbp-34h]
  int i_1; // [rsp+10h] [rbp-30h]
  int i_0; // [rsp+14h] [rbp-2Ch]
  int i; // [rsp+18h] [rbp-28h]
  int index; // [rsp+1Ch] [rbp-24h]
  char *result; // [rsp+20h] [rbp-20h]
  int total; // [rsp+2Ch] [rbp-14h]

  total = 0;
  if ( a > 0 )
    total = a;
  if ( b > 0 )
    total += b;
  if ( c > 0 )
    total += c;
  if ( d > 0 )
    total += d;
  result = (char *)malloc(total + 1);
  if ( !result )
  {
    perror("Failed to allocate memory");
    exit(1);
  }
  index = 0;
  for ( i = 0; i < a; ++i )
  {
    v4 = index++;
    result[v4] = 112;
  }
  for ( i_0 = 0; i_0 < b; ++i_0 )
  {
    v5 = index++;
    result[v5] = 113;
  }
  for ( i_1 = 0; i_1 < c; ++i_1 )
  {
    v6 = index++;
    result[v6] = 114;
  }
  for ( i_2 = 0; i_2 < d; ++i_2 )
  {
    v7 = index++;
    result[v7] = 115;
  }
  result[index] = 0;
  return result;
}