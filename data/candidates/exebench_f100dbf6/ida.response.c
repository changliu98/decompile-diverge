void __cdecl tea_decrypt(unsigned __int64 *v, unsigned __int64 *k)
{
  unsigned __int64 i; // [rsp+28h] [rbp-30h]
  unsigned __int64 sum; // [rsp+30h] [rbp-28h]
  unsigned __int64 v1; // [rsp+38h] [rbp-20h]
  unsigned __int64 v0; // [rsp+40h] [rbp-18h]

  v0 = *v;
  v1 = v[1];
  sum = 3337565984LL;
  for ( i = 0LL; i < 0x20; ++i )
  {
    v1 -= (k[3] + (v0 >> 5)) ^ (sum + v0) ^ (k[2] + 16 * v0);
    v0 -= (k[1] + (v1 >> 5)) ^ (sum + v1) ^ (*k + 16 * v1);
    sum -= 2654435769LL;
  }
  *v = v0;
  v[1] = v1;
}