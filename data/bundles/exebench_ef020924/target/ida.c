void __cdecl swapfloat(float *flt)
{
  *(_DWORD *)flt = ((*(_DWORD *)flt & 0xFF000000) >> 24) | ((*(_DWORD *)flt & 0xFF0000u) >> 8) | ((*(_DWORD *)flt & 0xFF00) << 8) | ((unsigned __int8)*(_DWORD *)flt << 24);
}