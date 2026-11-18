int func0(int *array, int size) {
 int i = 0;
 char result;

 while (1) {
  if (i >= size) {
   result = 0;
   break;
  }
  else if (*(array + i) % 2 == 0) {
   result = 1;
   break;
  }
  else {
   i++;
  }
 }

 return result & 1;
}