void __cdecl std::swap[abi:nn200000]<double>(double *a, double *b)
{
  __int64 t; // [rsp+0h] [rbp-18h]

  t = *(_QWORD *)a;
  *a = *b;
  *(_QWORD *)b = t;
}