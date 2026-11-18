int func0(int a[], int x, int n){
  int low = 0;
  int high = n - 1;
  int mid;
  int res = -1;
  while (low <= high){
    mid = (low + high)/2;
    if (a[mid]>x){
      high = mid - 1;
    }
    else if (a[mid]<x){
      low = mid + 1;
    }
    else{
      res = mid;
      high = mid - 1;
    }
  }
  return res;
}