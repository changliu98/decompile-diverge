char *__cdecl unmakemask(int mask, char *smask)
{
  int i = 0;

  if (mask & 1) 
  {
    smask[i++] = 'c';
  }
  if (mask & 2) 
  {
    smask[i++] = 'r';
  }
  if (mask & 4) 
  {
    smask[i++] = 'l';
  }
  
  smask[i] = '\0';
  
  return smask;
}