int
imul_dbl(u_int64_t *mp)
{
 u_int64_t m0, m1, m2, m3;
 u_int128_t m;

 m0 = mp[0];
 m1 = mp[1];

 m = ((u_int128_t)m0) * m1;

 m2 = m & 0xffffffffffffffffULL;
 m3 = m >> 64;

 mp[0] = m2;
 mp[1] = m3;

 return (m3 != 0);
}