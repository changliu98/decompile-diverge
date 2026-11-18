void setIRQflag(char *flags)

{
  char *flags_local;
  
  flags[5] = '1';
  return;
}