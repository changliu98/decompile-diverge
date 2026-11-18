void __cdecl std::swap[abi:nn200000]<int>(int *k, int *i)
{
  int zero_buffer; // [rsp+0h] [rbp-14h]

  zero_buffer = *k;
  *k = *i;
  *i = zero_buffer;
}