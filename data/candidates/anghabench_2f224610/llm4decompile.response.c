int is_dup(int *seq, int index, int val)
{
 int i;
 for (i = 0; i < index; i++)
  if (seq[i] == val)
   return 1;
 return 0;
}