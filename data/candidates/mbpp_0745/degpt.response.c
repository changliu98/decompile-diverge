void func0(int startnum,int endnum,int *result,int *result_size)

{
  bool bVar1;
  int digit;
  int temp;
  _Bool divisible;
  int n;
  int *result_size_local;
  int *result_local;
  int endnum_local;
  int startnum_local;
  
  *result_size = 0;
  n = startnum;
  do {
    if (endnum < n) {
      return;
    }
    bVar1 = true;
    for (temp = n; 0 < temp; temp = temp / 10) {
      if ((temp % 10 == 0) || (n % (temp % 10) != 0)) {
        bVar1 = false;
        break;
      }
    }
    if (bVar1) {
      result[*result_size] = n;
      *result_size = *result_size + 1;
    }
    n = n + 1;
  } while( true );
}