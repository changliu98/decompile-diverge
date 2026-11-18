int
main (void)
{
  int len;
  unsigned char last_char, second_last_char;
  int result;

  len = strlen (name);
  if (len == 0)
    result = 0;
  else
    {
      last_char = name[len - 1];
      if (!((*___ctype_b_loc ())[(int) (last_char)] & (unsigned short int) 1024))
 result = 0;
      else
 {
   if (len == 1)
     result = 1;
   else
     {
       second_last_char = name[len - 2];
       if ((*___ctype_b_loc ())[(int) (second_last_char)] & (unsigned short int) 1024)
  result = 0;
       else
  result = 1;
     }
 }
    }

  return result;
}