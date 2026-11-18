void insertion_sort(char *a) {
 int j, i, key;
 for(j = 0; ; j++) {
  if(a[j + 1] == '\0') break;
  key = a[j + 1];
  i = j;
  while((key < a[i]) && (i > 0)) {
   a[i + 1] = a[i];
   i--;
  }
  a[i + 1] = key;
 }
}