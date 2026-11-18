void __cdecl decipher(unsigned __int64 *v, unsigned __int64 *k)
{
  unsigned __int64 sum; // [rsp+0h] [rbp-38h]
  unsigned __int64 i; // [rsp+10h] [rbp-28h]
  unsigned __int64 v1; // [rsp+18h] [rbp-20h]
  unsigned __int64 v0; // [rsp+20h] [rbp-18h]

  v0 = *v;
  v1 = v[1];
  sum = 0x1328B7BD67LL;
  for ( i = 0LL; i < 0x1F; ++i )
  {
    v1 -= (k[(sum >> 11) & 3] + sum) ^ (v0 + ((v0 >> 5) ^ (16 * v0)));
    sum -= 2654435769LL;
    v0 -= (k[sum & 3] + sum) ^ (v1 + ((v1 >> 5) ^ (16 * v1)));
  }
  *v = v0;
  v[1] = v1;
}