char * func0(char *numbers)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  char current [6];
  int k;
  int j;
  int i;
  int index;
  char *numto [10];
  int count [10];
  char *numbers_local;
  
  memset(count,0,0x28);
  memcpy(numto,&PTR_DAT_00103d90,0x50);
  index = 0;
  cVar1 = *numbers;
  do {
    if (cVar1 == '\0') {
      for (i = 0; i < 10; i = i + 1) {
        for (j = 0; j < count[i]; j = j + 1) {
          for (k = 0; numto[i][k] != '\0'; k = k + 1) {
            func0::out[index] = numto[i][k];
            index = index + 1;
          }
          func0::out[index] = ' ';
          index = index + 1;
        }
      }
      if (index < 1) {
        func0::out[0] = '\0';
      }
      else {
        func0::out[index + -1] = '\0';
      }
      return func0::out;
    }
    i = 0;
    while( true ) {
      bVar3 = false;
      if (numbers[i] != ' ') {
        bVar3 = numbers[i] != '\0';
      }
      if (!bVar3) break;
      current[i] = numbers[i];
      i = i + 1;
    }
    current[i] = '\0';
    for (j = 0; j < 10; j = j + 1) {
      iVar2 = strcmp(current,numto[j]);
      if (iVar2 == 0) {
        count[j] = count[j] + 1;
        break;
      }
    }
    numbers = numbers + (i + 1);
    cVar1 = numbers[-1];
  } while( true );
}