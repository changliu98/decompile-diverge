void __cdecl std::swap[abi:nn200000]<int>(int *Aj, int *Aj1)
{
  int originAj; // [rsp+0h] [rbp-14h]

  originAj = *Aj;
  *Aj = *Aj1;
  *Aj1 = originAj;
}