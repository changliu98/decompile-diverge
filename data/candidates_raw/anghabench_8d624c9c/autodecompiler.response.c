int ft_toupper(int c)
{
 int res;

 if (c >= 'a' && c <= 'z')
  res = c - ('a' - 'A');
 else
  res = c;
 return (res);
}