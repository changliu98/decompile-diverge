char last_char(char *ptr)

{
  char c;
  char *ptr_local;
  char local_9;
  
  if ((ptr == (char *)0x0) || (ptr_local = ptr, *ptr == '\0')) {
    local_9 = '\0';
  }
  else {
    for (; *ptr_local != '\0'; ptr_local = ptr_local + 1) {
    }
    local_9 = ptr_local[-1];
    ptr_local[-1] = '\0';
  }
  return local_9;
}