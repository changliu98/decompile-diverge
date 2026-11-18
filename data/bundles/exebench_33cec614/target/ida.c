void __cdecl std::swap[abi:nn200000]<double>(double *pa, double *pb)
{
  __int64 temp; // [rsp+0h] [rbp-18h]

  temp = *(_QWORD *)pa;
  *pa = *pb;
  *(_QWORD *)pb = temp;
}