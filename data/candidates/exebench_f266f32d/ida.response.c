void __cdecl getCpuid(unsigned int *p, unsigned int ax_0)
{
  _RAX = ax_0;
  __asm { cpuid }
  *p = _RAX;
  p[1] = _RBX;
  p[2] = _RCX;
  p[3] = _RDX;
}