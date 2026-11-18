int __cdecl find(float xt, float *x, int n)
{
  int itst; // [rsp+4h] [rbp-20h]
  int im; // [rsp+8h] [rbp-1Ch]
  int il; // [rsp+Ch] [rbp-18h]

  if ( *x >= xt )
    return 0;
  if ( xt >= x[n - 1] )
    return n - 1;
  il = 1;
  im = n;
  for ( itst = n - 1; itst > 1; itst = im - il )
  {
    if ( xt < x[(il + im) / 2 - 1] )
      im = (il + im) / 2;
    else
      il = (il + im) / 2;
  }
  return il - 1;
}