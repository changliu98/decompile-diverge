int func0(int *tup,int tup_size,int *lst,int lst_size)

{
  int j;
  int i;
  int count;
  int lst_size_local;
  int *lst_local;
  int tup_size_local;
  int *tup_local;
  
  count = 0;
  i = 0;
  do {
    if (tup_size <= i) {
      return count;
    }
    for (j = 0; j < lst_size; j = j + 1) {
      if (tup[i] == lst[j]) {
        count = count + 1;
        break;
      }
    }
    i = i + 1;
  } while( true );
}