const char *__cdecl func0(unsigned int x)
{
  if ( (((unsigned __int8)(((((((((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 4) ^ (((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 8) ^ (((((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 4) ^ (((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 16) ^ (unsigned __int8)(((unsigned __int16)((((((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 4) ^ (((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 8) ^ (((((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x) >> 4) ^ (((x >> 1) ^ x) >> 2) ^ (x >> 1) ^ x)) & 1) != 0 )
    return "Odd Parity";
  else
    return "Even Parity";
}