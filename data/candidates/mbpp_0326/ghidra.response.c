char * func0(int n,char **test_list)

{
  bool bVar1;
  int iVar2;
  ushort **ppuVar3;
  int i_1;
  int index;
  int max;
  int j_1;
  int found_1;
  int j;
  int found;
  int pos;
  char word [50];
  char *str;
  int i;
  int unique;
  char **test_list_local;
  int n_local;
  
  unique = 0;
  i = 0;
  do {
    if (n <= i) {
      max = 0;
      index = 0;
      for (i_1 = 0; i_1 < unique; i_1 = i_1 + 1) {
        if (max < func0::words[i_1].count) {
          max = func0::words[i_1].count;
          index = i_1;
        }
      }
      return func0::words[index].word;
    }
    str = test_list[i];
    pos = 0;
    for (; *str != '\0'; str = str + 1) {
      ppuVar3 = __ctype_b_loc();
      if (((*ppuVar3)[(int)*str] & 0x2000) == 0) {
        word[pos] = *str;
        pos = pos + 1;
      }
      else if (0 < pos) {
        word[pos] = '\0';
        bVar1 = false;
        for (j = 0; j < unique; j = j + 1) {
          iVar2 = strcmp(func0::words[j].word,word);
          if (iVar2 == 0) {
            func0::words[j].count = func0::words[j].count + 1;
            bVar1 = true;
            break;
          }
        }
        if (!bVar1) {
          strcpy(func0::words[unique].word,word);
          func0::words[unique].count = 1;
          unique = unique + 1;
        }
        pos = 0;
      }
    }
    if (0 < pos) {
      word[pos] = '\0';
      bVar1 = false;
      for (j_1 = 0; j_1 < unique; j_1 = j_1 + 1) {
        iVar2 = strcmp(func0::words[j_1].word,word);
        if (iVar2 == 0) {
          func0::words[j_1].count = func0::words[j_1].count + 1;
          bVar1 = true;
          break;
        }
      }
      if (!bVar1) {
        strcpy(func0::words[unique].word,word);
        func0::words[unique].count = 1;
        unique = unique + 1;
      }
    }
    i = i + 1;
  } while( true );
}