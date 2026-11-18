void set_mac(char *setto,char *from)

{
  int i;
  char *from_local;
  char *setto_local;
  
  for (i = 0; i < 6; i = i + 1) {
    setto[i] = from[i];
  }
  return;
}