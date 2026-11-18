void __cdecl std::swap[abi:nn200000]<int>(int *u, int *v)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *u;
  *u = *v;
  *v = temp;
}