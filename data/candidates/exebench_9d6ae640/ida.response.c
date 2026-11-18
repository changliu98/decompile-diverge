void __cdecl cpuinfo(int code, int *eax_0, int *ebx_0, int *ecx_0, int *edx_0)
{
  _RAX = (unsigned int)code;
  __asm { cpuid }
  *eax_0 = _RAX;
  *ebx_0 = _RBX;
  *ecx_0 = _RCX;
  *edx_0 = _RDX;
}