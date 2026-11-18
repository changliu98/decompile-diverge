char *
func0(char *str1)
{
 int i, j;

 for (i = 0, j = 0; str1[i] != '\0'; i++) {
  if (!(__ctype_b_loc()->__ctype_b[str1[i]] & 0x200)) {
   func0::result[j++] = str1[i];
  }
 }
 func0::result[j] = '\0';

 return func0::result;
}