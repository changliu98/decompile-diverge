int func0(char *str)

{
  size_t sVar1;
  int i;
  int upper_ctr;
  char *str_local;
  undefined4 local_c;
  
  upper_ctr = 0;
  sVar1 = strlen(str);
  if (sVar1 != 0) {
    if (('@' < *str) && (*str < '[')) {
      upper_ctr = 1;
    }
    local_c = upper_ctr;
  }
  return local_c;
}