_Bool func0(int n)

{
  int count;
  int temp;
  int i;
  int n_local;
  
  i = 0;
  do {
    if (9 < i) {
      return true;
    }
    count = 0;
    for (temp = n; 0 < temp; temp = temp / 10) {
      if (temp % 10 == i) {
        count = count + 1;
      }
      if (i < count) {
        return false;
      }
    }
    i = i + 1;
  } while( true );
}