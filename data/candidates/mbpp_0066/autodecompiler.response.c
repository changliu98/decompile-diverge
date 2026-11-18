int func0(int *list, int size) {
 int i;
 int count = 0;

 for (i = 0; i < size; i++) {
  if (list[i] >= 0)
   count++;
 }

 return count;
}