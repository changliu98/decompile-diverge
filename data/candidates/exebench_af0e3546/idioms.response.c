void set_mac(char *set, char *get)
{
  int i;
  for (i = 0; i < 6; i++)
    set[i] = get[i];
}