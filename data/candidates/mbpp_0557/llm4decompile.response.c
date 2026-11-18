char * func0(char * string)
{
 int i;
 strcpy(toggled_string, string);
 for (i = 0; toggled_string[i] != '\0'; i++)
 {
  if ( ((*__ctype_b_loc ())[(int) ((toggled_string[i]))] & (0x100)) )
   toggled_string[i] = tolower(toggled_string[i]);
  else if ( ((*__ctype_b_loc ())[(int) ((toggled_string[i]))] & (0x200)) )
   toggled_string[i] = toupper(toggled_string[i]);
 }
 return toggled_string;
}