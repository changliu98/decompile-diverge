void __cdecl swap_float_4(float *tnf4)
{
  *(_DWORD *)tnf4 = ((*(_DWORD *)tnf4 & 0xFF00) << 8) | (*(int *)tnf4 >> 8) & 0xFF00 | ((unsigned __int8)*(_DWORD *)tnf4 << 24) | (unsigned __int8)HIBYTE(*(_DWORD *)tnf4);
}