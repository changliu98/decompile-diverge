void __cdecl std::swap[abi:nn200000]<float>(float *a, float *b)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *(_DWORD *)a;
  *a = *b;
  *(_DWORD *)b = temp;
}