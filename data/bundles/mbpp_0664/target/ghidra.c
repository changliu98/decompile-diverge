int func0(int n)

{
  int count;
  int sm;
  int n_local;
  int local_c;
  
  if (n % 2 == 0) {
    sm = 0;
    count = 0;
    for (n_local = n; 1 < n_local; n_local = n_local + -2) {
      count = count + 1;
      sm = n_local + sm;
    }
    local_c = sm / count;
  }
  else {
    printf("Invalid Input\n");
    local_c = -1;
  }
  return local_c;
}