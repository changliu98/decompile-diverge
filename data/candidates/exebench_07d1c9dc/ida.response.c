void __cdecl cpuid_count(int op, int count, int *eax_0, int *ebx_0, int *ecx_0, int *edx_0)
{
  _RAX = (unsigned int)op;
  __asm { cpuid }
  *eax_0 = _RAX;
  *ebx_0 = _RBX;
  *ecx_0 = _RCX;
  *edx_0 = _RDX;
}