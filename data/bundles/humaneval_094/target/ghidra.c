int func0(int *lst,int size)

{
  bool bVar1;
  int local_34;
  int j;
  int prime;
  int i;
  int temp;
  int num;
  int sum;
  int largest;
  int size_local;
  int *lst_local;
  
  largest = 0;
  sum = 0;
  i = 0;
  do {
    if (size <= i) {
      for (; 0 < largest; largest = largest / 10) {
        sum = largest % 10 + sum;
      }
      return sum;
    }
    local_34 = lst[i];
    if (1 < local_34) {
      bVar1 = true;
      for (j = 2; j * j <= local_34; j = j + 1) {
        if (local_34 % j == 0) {
          bVar1 = false;
          break;
        }
      }
      if (bVar1) {
        if (local_34 <= largest) {
          local_34 = largest;
        }
        largest = local_34;
      }
    }
    i = i + 1;
  } while( true );
}