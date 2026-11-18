void __cdecl cpuid(unsigned int op, unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
  _RAX = op;
  __asm { cpuid }
  *eax_0 = _RAX;
  *ebx_0 = _RBX;
  *ecx_0 = _RCX;
  *edx_0 = _RDX;
}