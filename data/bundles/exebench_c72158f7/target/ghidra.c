double rnd(long *prandom)

{
  long *prandom_local;
  
  *prandom = (*prandom * 0x6255 + 0x3619) % 0x10000;
  return (double)*prandom / DAT_00102008;
}