void __cdecl jpq_cpuid_custom(int *CPUInfo, int InfoType)
{
  _RAX = (unsigned int)InfoType;
  __asm { cpuid }
  *CPUInfo = _RAX;
  CPUInfo[1] = _RBX;
  CPUInfo[2] = _RCX;
  CPUInfo[3] = _RDX;
}