void __cdecl ut32_unpack(char *s, unsigned int *u)
{
  *u =  (uint8_t)s[0]       | 
       ((uint8_t)s[1] << 8)  | 
       ((uint8_t)s[2] << 16) | 
       ((uint8_t)s[3] << 24);
}