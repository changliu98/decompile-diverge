void __cdecl advance_spos(int *spos)
{
  *spos = (*spos + 1) % 43;
  spos[1] = (spos[1] + 1) % 47;
  spos[2] = (spos[2] + 1) % 51;
  spos[3] = (spos[3] + 1) % 53;
  spos[4] = (spos[4] + 1) % 59;
}