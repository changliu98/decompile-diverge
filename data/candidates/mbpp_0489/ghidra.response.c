int func0(int n,int *arr)

{
  int i;
  int freq;
  int mn;
  int *arr_local;
  int n_local;
  
  mn = *arr;
  freq = 1;
  for (i = 1; i < n; i = i + 1) {
    if (mn < arr[i]) {
      mn = arr[i];
      freq = 1;
    }
    else if (arr[i] == mn) {
      freq = freq + 1;
    }
  }
  return freq;
}