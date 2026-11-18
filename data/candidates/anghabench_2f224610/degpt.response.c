bool is_dup(int *seq,int index,int val)

{
  int i;
  int val_local;
  int index_local;
  int *seq_local;
  
  i = 0;
  while( true ) {
    if (index <= i) {
      return 0;
    }
    if (seq[i] == val) break;
    i = i + 1;
  }
  return 1;
}