int ether_hash(char *str)
{
 int i;
 int h;

 h = 0;
 i = 0;
 while (1)
 {
  if (i < 7)
  {
   h = str[i] + (h << 6) + (h << 16) - h;
   i++;
  }
  else
   return (h);
 }
}