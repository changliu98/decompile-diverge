void set_stimulus(unsigned char *ip, char *mask)
{
  for (; *mask; mask++)
    if (*mask >= '0' && *mask <= '7')
      *ip = *ip & ~(1 << (*mask - '0'));
}