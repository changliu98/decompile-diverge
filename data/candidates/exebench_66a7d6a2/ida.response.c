void __cdecl swapdouble(double *dbl)
{
  int t; // [rsp+Ch] [rbp-Ch]

  t = ((*(_DWORD *)dbl & 0xFF000000) >> 24) | ((*(_DWORD *)dbl & 0xFF0000u) >> 8) | ((*(_DWORD *)dbl & 0xFF00) << 8) | ((unsigned __int8)*(_DWORD *)dbl << 24);
  *(_DWORD *)dbl = ((*((_DWORD *)dbl + 1) & 0xFF000000) >> 24) | ((*((_DWORD *)dbl + 1) & 0xFF0000u) >> 8) | ((*((_DWORD *)dbl + 1) & 0xFF00) << 8) | ((unsigned __int8)*((_DWORD *)dbl + 1) << 24);
  *((_DWORD *)dbl + 1) = t;
}