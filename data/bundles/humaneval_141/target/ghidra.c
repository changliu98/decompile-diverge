char * func0(char *file_name)

{
  char cVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  char *__s1;
  int i;
  char *last;
  char w;
  int length;
  int num_dot;
  int num_digit;
  char *file_name_local;
  char *local_10;
  
  num_digit = 0;
  num_dot = 0;
  sVar4 = strlen(file_name);
  iVar2 = (int)sVar4;
  if (iVar2 < 5) {
    local_10 = "No";
  }
  else {
    cVar1 = *file_name;
    if ((cVar1 < 'A') || ((('Z' < cVar1 && (cVar1 < 'a')) || ('z' < cVar1)))) {
      local_10 = "No";
    }
    else {
      __s1 = file_name + (long)iVar2 + -4;
      iVar3 = strcmp(__s1,".txt");
      if (((iVar3 != 0) && (iVar3 = strcmp(__s1,".exe"), iVar3 != 0)) &&
         (iVar3 = strcmp(__s1,".dll"), iVar3 != 0)) {
        return "No";
      }
      for (i = 0; i < iVar2; i = i + 1) {
        if (('/' < file_name[i]) && (file_name[i] < ':')) {
          num_digit = num_digit + 1;
        }
        if (file_name[i] == '.') {
          num_dot = num_dot + 1;
        }
      }
      if ((num_digit < 4) && (num_dot == 1)) {
        local_10 = "Yes";
      }
      else {
        local_10 = "No";
      }
    }
  }
  return local_10;
}