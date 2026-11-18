char *func0(char *str)
{
 int i;
 int j;

 i = 0;
 j = 0;
 while (1) {
  if (str[i] == '\0') {
   func0_buffer[j] = '\0';
   return func0_buffer;
  }
  if ((((((((unsigned short int) *(*__ctype_b_loc () + (int) (str[i])))) & (unsigned short int) 256)) != 0))) {
   if ((i != 0) && ((((unsigned short int) *(*__ctype_b_loc () + (int) (str[i - 1])))) & (unsigned short int) 512)) || ((((unsigned short int) *(*__ctype_b_loc () + (int) (str[i - 1])))) & (unsigned short int) 2048))) {
    func0_buffer[j++] = '_';
   }
   func0_buffer[j++] = tolower(str[i]);
  } else {
   func0_buffer[j++] = str[i];
  }
  i++;
 }
}