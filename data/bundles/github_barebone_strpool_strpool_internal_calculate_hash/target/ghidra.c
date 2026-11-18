uint strpool_internal_calculate_hash(char *string,int length,int ignore_case)

{
  char cVar1;
  uint local_34;
  char c_1;
  int i_1;
  char c;
  int i;
  uint hash;
  int ignore_case_local;
  int length_local;
  char *string_local;
  
  hash = 0x1505;
  if (ignore_case == 0) {
    for (i_1 = 0; i_1 < length; i_1 = i_1 + 1) {
      hash = hash * 0x21 ^ (int)string[i_1];
    }
  }
  else {
    for (i = 0; i < length; i = i + 1) {
      cVar1 = string[i];
      if ((cVar1 < '{') && ('`' < cVar1)) {
        cVar1 = cVar1 + -0x20;
      }
      hash = hash * 0x21 ^ (int)cVar1;
    }
  }
  if (hash == 0) {
    local_34 = 1;
  }
  else {
    local_34 = hash;
  }
  return local_34;
}