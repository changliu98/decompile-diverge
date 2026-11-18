int func0(int n)

{
  int count;
  int sm;
  int n_local;
  int local_c;
  
  if (n % 2 == 0) {
    printf("Invalid Input\n");
    local_c = -1;
  }
  else {
    sm = 0;
    count = 0;
    for (n_local = n; 0 < n_local; n_local = n_local + -2) {
      count = count + 1;
      sm = n_local + sm;
    }
    local_c = sm / count;
  }
  return local_c;
}