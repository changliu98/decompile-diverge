_Bool func0(char *s0,char *s1)

{
  bool bVar1;
  size_t sVar2;
  size_t sVar3;
  int j_1;
  _Bool found_1;
  int i_1;
  int j;
  _Bool found;
  int i;
  int len1;
  int len0;
  char *s1_local;
  char *s0_local;
  
  sVar2 = strlen(s0);
  sVar3 = strlen(s1);
  for (i = 0; i < (int)sVar2; i = i + 1) {
    bVar1 = false;
    for (j = 0; j < (int)sVar3; j = j + 1) {
      if (s0[i] == s1[j]) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      return false;
    }
  }
  i_1 = 0;
  do {
    if ((int)sVar3 <= i_1) {
      return true;
    }
    bVar1 = false;
    for (j_1 = 0; j_1 < (int)sVar2; j_1 = j_1 + 1) {
      if (s1[i_1] == s0[j_1]) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      return false;
    }
    i_1 = i_1 + 1;
  } while( true );
}