void __cdecl std::swap[abi:nn200000]<int>(int *one, int *two)
{
  int aux; // [rsp+0h] [rbp-14h]

  aux = *one;
  *one = *two;
  *two = aux;
}