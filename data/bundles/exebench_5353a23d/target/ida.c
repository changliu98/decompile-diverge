void __cdecl std::swap[abi:nn200000]<std::__function::__policy const*>(size_t *first, size_t *second)
{
  size_t temp; // [rsp+0h] [rbp-18h]

  temp = *first;
  *first = *second;
  *second = temp;
}