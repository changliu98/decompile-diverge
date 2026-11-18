void __cdecl atomic_retain(volatile int *p)
{
  _InterlockedAdd(p, 1u);
}