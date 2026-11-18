void __cdecl htonf(float *x)
{
  *(_DWORD *)x = htonl(*(_DWORD *)x);
}