void func0(int num,int *result)

{
  int digit;
  int odd_count;
  int even_count;
  int *result_local;
  int num_local;
  
  even_count = 0;
  odd_count = 0;
  num_local = abs(num);
  do {
    if ((num_local % 10) % 2 == 0) {
      even_count = even_count + 1;
    }
    else {
      odd_count = odd_count + 1;
    }
    num_local = num_local / 10;
  } while (0 < num_local);
  *result = even_count;
  result[1] = odd_count;
  return;
}