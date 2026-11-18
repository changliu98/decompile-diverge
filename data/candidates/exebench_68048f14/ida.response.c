void __cdecl vinv(double *v)
{
  *(_QWORD *)v ^= 0x8000000000000000LL;
  *((_QWORD *)v + 1) ^= 0x8000000000000000LL;
  *((_QWORD *)v + 2) ^= 0x8000000000000000LL;
}