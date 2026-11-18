bool __cdecl alps_check_valid_firmware_id(unsigned __int8 *id)
{
  return *id == 115 || *id == 136 && (id[1] == 7 || id[1] == 8 || (id[1] & 0xF0) == 176 || (id[1] & 0xF0) == 192);
}