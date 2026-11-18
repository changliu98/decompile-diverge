int equi ( int A[], int N ) {
  int a = 0;
  int b = 0;
  int i;
  int sum = 0;

  for(i = 0; i < N; i++) {
      sum += A[i];
  }

  int left_sum = 0;
  int right_sum = 0;

  for(i = 0; i < N; i++) {
      sum -= A[i];

      if(left_sum == sum) {
          return i;
      } else {
          left_sum += A[i];
      }
  }

  return -1;
}