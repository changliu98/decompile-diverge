char * func0(char *string)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  int index;
  char *result;
  int new_length;
  int space_count;
  int j;
  int i;
  char new_string [1000];
  char *string_local;
  char *local_10;
  
  space_count = 0;
  sVar3 = strlen(string);
  iVar1 = (int)sVar3;
  for (j = 0; j < iVar1; j = j + 1) {
    if (string[j] == ' ') {
      space_count = space_count + 1;
    }
  }
  iVar2 = iVar1 + space_count * 2;
  if (iVar2 < 0x3e9) {
    index = iVar2 + -1;
    new_string[iVar2] = '\0';
    j = iVar1;
    while (j = j + -1, -1 < j) {
      if (string[j] == ' ') {
        new_string[index] = '0';
        new_string[index + -1] = '2';
        new_string[index + -2] = '%';
        index = index + -3;
      }
      else {
        new_string[index] = string[j];
        index = index + -1;
      }
    }
    local_10 = malloc((long)(iVar2 + 1));
    strcpy(local_10,new_string);
  }
  else {
    local_10 = "";
  }
  return local_10;
}