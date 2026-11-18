_Bool func0(int x)

{
  int iVar1;
  int j;
  int i;
  int next_term;
  int temp_1;
  int right;
  int left;
  int n;
  int temp;
  int terms [100];
  int x_local;
  
  n = 0;
  for (temp = x; 0 < temp; temp = temp / 10) {
    terms[n] = temp % 10;
    n = n + 1;
  }
  right = n;
  for (left = 0; right = right + -1, left < right; left = left + 1) {
    iVar1 = terms[left];
    terms[left] = terms[right];
    terms[right] = iVar1;
  }
  next_term = 0;
  i = n;
  while (next_term < x) {
    next_term = 0;
    for (j = 1; j <= n; j = j + 1) {
      next_term = terms[i - j] + next_term;
    }
    terms[i] = next_term;
    i = i + 1;
  }
  return next_term == x;
}