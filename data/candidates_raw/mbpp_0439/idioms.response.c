int arrayToInt(int *array, int size){
  int i;
  int *arr = array;
  int len = size;
  char temp[256];
  char num[20];
  memset(temp, '\0', sizeof(temp));
  for(i = 0; i < len; i++){
    sprintf(num, "%d", arr[i]);
    strcat(temp, num);
  }
  return atoi(temp);
}