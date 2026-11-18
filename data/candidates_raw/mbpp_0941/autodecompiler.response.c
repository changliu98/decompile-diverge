int count(int *arr, int size) {
 int i;
 int count = 0;

 for (i = 0; ; i++) {
  if (i >= size || arr[i] == -1)
   break;
  count++;
 }

 return count;
}