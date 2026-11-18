void __cdecl run_cpuid(int eax_0, int ecx_0, int *abcd)
{
  _RAX = (unsigned int)eax_0;
  __asm { cpuid }
  *abcd = _RAX;
  abcd[1] = _RBX;
  abcd[2] = _RCX;
  abcd[3] = _RDX;
}