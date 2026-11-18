int __cdecl imul_dbl(unsigned __int64 *m)
{
  __int128 v1; // rax

  v1 = (__int64)m[1] * (__int128)(__int64)*m;
  *(_OWORD *)m = __PAIR128__(*((unsigned __int64 *)&v1 + 1), m[1] * *m);
  return *((_QWORD *)&v1 + 1) != 0LL;
}