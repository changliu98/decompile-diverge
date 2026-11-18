void __cdecl std::swap[abi:nn200000]<float>(float *valueA, float *valueB)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *(_DWORD *)valueA;
  *valueA = *valueB;
  *(_DWORD *)valueB = temp;
}