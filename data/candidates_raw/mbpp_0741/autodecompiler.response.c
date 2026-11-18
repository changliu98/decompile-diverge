int check_base_condition(char *base_from)
{
 int l;
 int it;

 l = strlen(base_from);
 it = 1;
 while (it < l)
 {
  if (base_from[it] != base_from[0])
  {
   it = 0;
   break ;
  }
  it++;
 }
 return (it == 0 ? 0 : 1);
}