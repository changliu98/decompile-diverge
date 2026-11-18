void __cdecl std::swap[abi:nn200000]<float>(float *a, float *b)
{
  int t; // [rsp+0h] [rbp-14h]

  t = *(_DWORD *)a;
  *a = *b;
  *(_DWORD *)b = t;
}