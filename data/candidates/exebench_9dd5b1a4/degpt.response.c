int add_char_to_string(char *string,char c,int size)

{
  int i;
  int size_local;
  char c_local;
  char *string_local;
  int local_c;
  
  if (string == (char *)0x0) {
    local_c = 0;
  }
  else {
    for (i = 0; string[i] != '\0'; i = i + 1) {
    }
    if (i < size + -1) {
      string[i] = c;
      string[i + 1] = '\0';
      local_c = 1;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}