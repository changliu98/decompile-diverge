int __cdecl func0(int p, int q, int N)
{
  int res; // [rsp+0h] [rbp-10h]
  int pb; // [rsp+Ch] [rbp-4h]

  while ( N > 0 )
  {
    --N;
    pb = 10 * p;
    res = pb / q;
    p = pb % q;
  }
  return res;
}