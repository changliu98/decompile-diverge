struct yankreg *get_register(int regno, int copy)
{
  int i;
  struct yankreg *reg;
  y_setreg(regno, 0);
  if ((reg = (struct yankreg *) y_malloc(sizeof(struct yankreg))) == (struct yankreg *) ((void *)0))
    return ((void *)0);
  reg->y_array = y_current->y_array;
  reg->y_size = y_current->y_size;
  reg->y_type = y_current->y_type;
  if (copy)
    {
      if (reg->y_size == 0)
 reg->y_array = ((void *)0);
      else
 {
   reg->y_array = (char **) y_malloc(reg->y_size * sizeof(char *));
 }
      if (reg->y_array != ((void *)0))
 {
   for (i = 0; i < reg->y_size; i++)
     reg->y_array[i] = y_strdup(y_current->y_array[i]);
 }
    }
  else
    y_current->y_array = ((void *)0);
  return (reg);
}