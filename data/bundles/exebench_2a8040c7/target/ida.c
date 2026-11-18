long __cdecl shmDetach(float *addr)
{
  return shmdt(addr);
}