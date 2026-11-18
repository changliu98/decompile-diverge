void ut32_unpack(char *s,uint *u)

{
  uint result;
  uint *u_local;
  char *s_local;
  
  *u = (uint)(byte)*s +
       ((uint)(byte)s[1] + ((uint)(byte)s[2] + (uint)(byte)s[3] * 0x100) * 0x100) * 0x100;
  return;
}