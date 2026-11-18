int ok_cp1251(char *str, int len)
{
 int i;
 int ret;

 i = 1;
 while (1)
 {
  if (i < len)
  {
   switch (str[i])
   {
    case -104:
     ret = 0;
     break;
    default:
     i++;
     continue;
   }
  }
  else
   ret = 1;
  break ;
 }
 return (ret);
}