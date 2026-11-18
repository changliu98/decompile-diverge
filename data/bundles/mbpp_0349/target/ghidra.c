char * func0(char *string)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  size_t sVar4;
  int i;
  int hasOther;
  int has1;
  int has0;
  char *string_local;
  char *local_10;
  
  bVar1 = false;
  bVar2 = false;
  bVar3 = false;
  i = 0;
  do {
    sVar4 = strlen(string);
    if (sVar4 <= (ulong)(long)i) {
LAB_0010127f:
      if (((!bVar1) && (!bVar2)) || (bVar3)) {
        local_10 = "No";
      }
      else {
        local_10 = "Yes";
      }
      return local_10;
    }
    if (string[i] == '0') {
      bVar1 = true;
    }
    else {
      if (string[i] != '1') {
        bVar3 = true;
        goto LAB_0010127f;
      }
      bVar2 = true;
    }
    i = i + 1;
  } while( true );
}