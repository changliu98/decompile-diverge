int *func0(int *nums, int size){
  int *num = nums;
  int *sumdigit = (int *)malloc(size * sizeof(int));
  int i;
  for(i = 0; i < size; i++){
    char str[12];
    int sum = 0;
    int length = 0;
    int j;
    sprintf(str,"%d",abs(num[i]));
    length = strlen(str);
    for(j = 1; j < length; j++){
      sum += (str[j] - '0');
    }
    if(num[i] > 0){
      sum += (str[0] - '0');
    }
    else{
      sum -= (str[0] - '0');
    }
    sumdigit[i] = sum;
  }
  for(i = 0; i < size; i++){
    int k;
    for(k = 1; k < size; k++){
      if(sumdigit[k - 1] > sumdigit[k]){
        int temp = sumdigit[k];
        sumdigit[k] = sumdigit[k - 1];
        sumdigit[k - 1] = temp;
        int temp2 = num[k];
        num[k] = num[k - 1];
        num[k - 1] = temp2;
      }
    }
  }
  free(sumdigit);
  return num;
}