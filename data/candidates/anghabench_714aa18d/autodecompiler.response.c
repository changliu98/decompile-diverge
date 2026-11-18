int is_valid_ref_char(char c)
{
 int i;
 int result;

 if ((unsigned)c <= 32)
  result = 0;
 else
 {
  i = (int)c;
  if (i == 42 || i == 58 || i == 63 || i == 91 || i == 93 || i == 94 || i == 126)
   result = 0;
  else
   result = 1;
 }
 return (result);
}