char *func0(int *array, int length){
 char *yes = "YES";
 char *no = "NO";
 int i;
 for(i = 1; ; i++){
  if(i >= length) break;
  if(array[i] != array[0]) {
   return no;
  }
 }
 return yes;
}