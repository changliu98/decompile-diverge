void __cdecl native_cpuid(unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
  _RAX = *eax_0;
  __asm { cpuid }
  *eax_0 = _RAX;
  *ebx_0 = _RBX;
  *ecx_0 = _RCX;
  *edx_0 = _RDX;
}