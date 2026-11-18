char ** func0(char **arr1,int n1,char **arr2,int n2)

{
  size_t sVar1;
  int sum2;
  int sum1;
  int i;
  int n2_local;
  char **arr2_local;
  int n1_local;
  char **arr1_local;
  char **local_10;
  
  sum1 = 0;
  sum2 = 0;
  for (i = 0; i < n1; i = i + 1) {
    sVar1 = strlen(arr1[i]);
    sum1 = sum1 + (int)sVar1;
  }
  for (i = 0; i < n2; i = i + 1) {
    sVar1 = strlen(arr2[i]);
    sum2 = sum2 + (int)sVar1;
  }
  local_10 = arr1;
  if ((sum2 <= sum1) && (sum2 < sum1)) {
    local_10 = arr2;
  }
  return local_10;
}