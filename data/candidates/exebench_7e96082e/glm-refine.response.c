void __cdecl atomic_dec(volatile int *v)
{
  _InterlockedDecrement(v);
}