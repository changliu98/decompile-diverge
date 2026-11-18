_Bool func0(int *data,int length)

{
  int j;
  int i;
  int length_local;
  int *data_local;
  
  i = 0;
  do {
    j = i;
    if (length <= i) {
      return true;
    }
    while (j = j + 1, j < length) {
      if (data[i] == data[j]) {
        return false;
      }
    }
    i = i + 1;
  } while( true );
}