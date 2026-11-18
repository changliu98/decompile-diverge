void __cdecl get_payload_info(char *bzimage, int *offset, int *size)
{
  *offset = *((_DWORD *)bzimage + 146) + ((unsigned __int8)(bzimage[497] + 1) << 9);
  *size = *((_DWORD *)bzimage + 147);
}