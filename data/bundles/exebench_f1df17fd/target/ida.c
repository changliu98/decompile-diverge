int __cdecl FNEGQ(unsigned __int64 *rd, unsigned __int64 *rs2)
{
  *rd = *rs2 ^ 0x8000000000000000LL;
  rd[1] = rs2[1];
  return 1;
}