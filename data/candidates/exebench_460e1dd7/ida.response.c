void __cdecl BinaryFiles__swap_bytes32(unsigned int *value)
{
  *value = ((*value & 0xFF000000) >> 24)
         + ((*value & 0xFF0000) >> 8)
         + ((*value & 0xFF00) << 8)
         + ((unsigned __int8)*value << 24);
}