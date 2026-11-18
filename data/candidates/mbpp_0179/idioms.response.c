int func0(int n)
{
  int i; int j;
  int terms[100];
  int temp;
  int left; int right;
  int temp_0;
  int next_term;
  int n_digits = 0;
  temp = n;
  for (i = 0; i < n; i++)
  {
    terms[i] = temp % 10;
    temp = temp / 10;
  }
  left = 0;
  right = n - 1;
  while (left < right)
  {
    temp_0 = terms[left];
    terms[left] = terms[right];
    terms[right] = temp_0;
    left++;
    right--;
  }
  next_term = 0;
  for (i = n; next_term < n;)
  {
    next_term = 0;
    for (j = 1; j <= n; j++)
      next_term += terms[i - j];
    terms[i++] = next_term;
  }
  if (next_term == n)
    return 1;
  return 0;
}