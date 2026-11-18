int func0(int *arr,int n)

{
  int i;
  int maxEle;
  int minEle;
  int n_local;
  int *arr_local;
  
  minEle = *arr;
  maxEle = *arr;
  for (i = 1; i < n; i = i + 1) {
    if (arr[i] < minEle) {
      minEle = arr[i];
    }
    if (maxEle < arr[i]) {
      maxEle = arr[i];
    }
  }
  return maxEle - minEle;
}