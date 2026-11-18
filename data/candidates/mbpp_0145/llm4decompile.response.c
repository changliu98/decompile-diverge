int func0(int *arr, int n) {
 int i;
 int minEle, maxEle;

 minEle = arr[0];
 maxEle = arr[0];
 for (i = 1; i < n; i++) {
  if (arr[i] < minEle) {
   minEle = arr[i];
  }
  if (arr[i] > maxEle) {
   maxEle = arr[i];
  }
 }

 return maxEle - minEle;
}