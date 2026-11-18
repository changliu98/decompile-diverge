void __cdecl GetCPUInfo(int *cpu_info, int info_type)
{
  _RAX = (unsigned int)info_type;
  __asm { cpuid }
  *cpu_info = _RAX;
  cpu_info[1] = _RBX;
  cpu_info[2] = _RCX;
  cpu_info[3] = _RDX;
}