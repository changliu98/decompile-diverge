void numconv(char *numstr)

{
  char *numstr_local;
  
  numstr_local = numstr;
  while (*numstr_local != '\0') {
    *numstr_local = *numstr_local + -0x30;
    numstr_local = numstr_local + 1;
  }
  return;
}