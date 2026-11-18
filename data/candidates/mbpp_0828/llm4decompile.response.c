void func0(char *string, int *alphabets, int *digits, int *special)
{
 int i = 0;
 *special = 0;
 *digits = 0;
 *alphabets = 0;
 while (string[i] != '\0')
 {
  if ((*__ctype_b_loc ())[(int) ((string[i]))] & 0x400)
   *alphabets += 1;
  else if ((*__ctype_b_loc ())[(int) ((string[i]))] & 0x800)
   *digits += 1;
  else
   *special += 1;
  i++;
 }
}