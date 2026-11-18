void __cdecl std::swap[abi:nn200000]<std::__function::__policy const*>(long *a, long *b)
{
  long tmp; // [rsp+0h] [rbp-18h]

  tmp = *a;
  *a = *b;
  *b = tmp;
}