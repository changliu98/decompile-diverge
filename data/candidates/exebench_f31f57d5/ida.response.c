void __cdecl std::swap[abi:nn200000]<float>(float *n, float *m)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *(_DWORD *)n;
  *n = *m;
  *(_DWORD *)m = temp;
}