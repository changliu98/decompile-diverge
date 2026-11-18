char *func0(char *string)
{
 int i;
 strcpy(func0_toggled_string, string);
 for(i=0;;i++)
 {
  if(func0_toggled_string[i] == '\0') break;
  else if(((*___ctype_b_loc ())[(int) ((func0_toggled_string[i]))] & (unsigned short int) 256) != 0) func0_toggled_string[i] = tolower(func0_toggled_string[i]);
  else if(((*___ctype_b_loc ())[(int) ((func0_toggled_string[i]))] & (unsigned short int) 512) != 0) func0_toggled_string[i] = toupper(func0_toggled_string[i]);
 }
 return func0_toggled_string;
}