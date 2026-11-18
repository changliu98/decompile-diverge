char * func0(char *s1,char *s2)

{
  bool bVar1;
  size_t sVar2;
  size_t sVar3;
  int can;
  int i;
  int len2;
  int len1;
  int count;
  char *s2_local;
  char *s1_local;
  char *local_10;
  
  count = 0;
  sVar2 = strlen(s1);
  sVar3 = strlen(s2);
  bVar1 = true;
  for (i = 0; i < (int)sVar2; i = i + 1) {
    if (s1[i] == '(') {
      count = count + 1;
    }
    if (s1[i] == ')') {
      count = count + -1;
    }
    if (count < 0) {
      bVar1 = false;
    }
  }
  for (i = 0; i < (int)sVar3; i = i + 1) {
    if (s2[i] == '(') {
      count = count + 1;
    }
    if (s2[i] == ')') {
      count = count + -1;
    }
    if (count < 0) {
      bVar1 = false;
    }
  }
  if ((count == 0) && (bVar1)) {
    local_10 = "Yes";
  }
  else {
    count = 0;
    bVar1 = true;
    for (i = 0; i < (int)sVar3; i = i + 1) {
      if (s2[i] == '(') {
        count = count + 1;
      }
      if (s2[i] == ')') {
        count = count + -1;
      }
      if (count < 0) {
        bVar1 = false;
      }
    }
    for (i = 0; i < (int)sVar2; i = i + 1) {
      if (s1[i] == '(') {
        count = count + 1;
      }
      if (s1[i] == ')') {
        count = count + -1;
      }
      if (count < 0) {
        bVar1 = false;
      }
    }
    if ((count == 0) && (bVar1)) {
      local_10 = "Yes";
    }
    else {
      local_10 = "No";
    }
  }
  return local_10;
}