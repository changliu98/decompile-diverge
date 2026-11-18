void __cdecl to_bytes(int val, char *bytes)
{
  *bytes = val;
  *(_WORD *)(bytes + 1) = (unsigned int)val >> 8;
  bytes[3] = HIBYTE(val);
}