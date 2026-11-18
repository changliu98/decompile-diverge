void func0(char *string, char *uppercase_characters, char *lowercase_characters, char *numerical_characters, char *special_characters)
{
 int i;
 int upper_idx = 0;
 int lower_idx = 0;
 int num_idx = 0;
 int special_idx = 0;

 int len = strlen(string);

 for (i = 0; i < len; i++)
 {
  if ((*__ctype_b_loc ())[(int) string[i]] & (0x100))
  {
   uppercase_characters[upper_idx] = string[i];
   upper_idx++;
  }
  else if ((*__ctype_b_loc ())[(int) string[i]] & (0x200))
  {
   lowercase_characters[lower_idx] = string[i];
   lower_idx++;
  }
  else if ((*__ctype_b_loc ())[(int) string[i]] & (0x800))
  {
   numerical_characters[num_idx] = string[i];
   num_idx++;
  }
  else if (string[i] == ',' || string[i] == '.' || string[i] == '!' || string[i] == '?')
  {
   special_characters[special_idx] = string[i];
   special_idx++;
  }
 }

 uppercase_characters[upper_idx] = '\0';
 lowercase_characters[lower_idx] = '\0';
 numerical_characters[num_idx] = '\0';
 special_characters[special_idx] = '\0';
}