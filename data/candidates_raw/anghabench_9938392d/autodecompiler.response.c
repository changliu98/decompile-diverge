int ft_islower(int c)
{
 int ret;

 if (c >= 'a' && c <= 'z')
  ret = 1;
 else
  ret = 0;
 return (ret);
}