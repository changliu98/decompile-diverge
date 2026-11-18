int __cdecl paeth_predictor(int a, int b, int c)
{
  int v4; // [rsp+0h] [rbp-2Ch]
  int v5; // [rsp+4h] [rbp-28h]
  int v6; // [rsp+8h] [rbp-24h]
  int p; // [rsp+18h] [rbp-14h]

  p = b + a - c;
  if ( p <= a )
    v6 = c - b;
  else
    v6 = b - c;
  if ( p <= b )
    v5 = c - a;
  else
    v5 = a - c;
  if ( p <= c )
    v4 = c - p;
  else
    v4 = p - c;
  if ( v6 <= v5 && v6 <= v4 )
    return a;
  if ( v5 > v4 )
    return c;
  return b;
}