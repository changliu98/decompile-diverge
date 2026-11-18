_Bool func0(int num)

{
  int i;
  int num_local;
  _Bool local_9;
  
  if (num < 1) {
    local_9 = false;
  }
  else {
    for (i = 2; i <= num / 2; i = i + 1) {
      if (num % i == 0) {
        return false;
      }
    }
    local_9 = true;
  }
  return local_9;
}