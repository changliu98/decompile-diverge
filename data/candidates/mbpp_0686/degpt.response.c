char * func0(int *test_tup,int size)

{
  bool bVar1;
  char *__dest;
  int i_1;
  char buffer [50];
  char *result;
  int j;
  int found;
  int i;
  int count;
  dict freq [100];
  int size_local;
  int *test_tup_local;
  
  count = 0;
  i = 0;
  do {
    if (size <= i) {
      __dest = malloc(1000);
      *__dest = '\0';
      strcat(__dest,"{");
      for (i_1 = 0; i_1 < count; i_1 = i_1 + 1) {
        sprintf(buffer,"%d: %d",(ulong)(uint)freq[i_1].key,(ulong)(uint)freq[i_1].value);
        strcat(__dest,buffer);
        if (i_1 < count + -1) {
          strcat(__dest,", ");
        }
      }
      strcat(__dest,"}");
      return __dest;
    }
    bVar1 = false;
    for (j = 0; j < count; j = j + 1) {
      if (freq[j].key == test_tup[i]) {
        freq[j].value = freq[j].value + 1;
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      freq[count].key = test_tup[i];
      freq[count].value = 1;
      count = count + 1;
    }
    i = i + 1;
  } while( true );
}