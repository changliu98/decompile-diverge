void __cdecl ut32_unpack(char *s, unsigned int *u)
{
  *u = ((((((unsigned __int8)s[3] << 8) + (unsigned __int8)s[2]) << 8) + (unsigned __int8)s[1]) << 8)
     + (unsigned __int8)*s;
}