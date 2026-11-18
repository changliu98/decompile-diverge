void __cdecl std::swap[abi:nn200000]<float>(float *x, float *y)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *(_DWORD *)x;
  *x = *y;
  *(_DWORD *)y = temp;
}