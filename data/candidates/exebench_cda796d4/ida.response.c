void __cdecl std::swap[abi:nn200000]<std::__function::__policy const*>(long *p1, long *p2)
{
  long tmp; // [rsp+0h] [rbp-18h]

  tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}