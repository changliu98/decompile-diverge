int __cdecl get_opcode(unsigned __int8 *addr, unsigned int *opcode)
{
  if ( *addr == 15 )
  {
    *opcode = *(unsigned __int16 *)addr;
    return 2;
  }
  else
  {
    *opcode = *addr;
    return 1;
  }
}