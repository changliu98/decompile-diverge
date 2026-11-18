void __cdecl calculate_crc(char *crc, char newval)
{
  *crc ^= newval;
}