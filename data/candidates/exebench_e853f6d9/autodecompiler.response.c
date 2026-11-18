int summe(int *a, int *b){

 if(*a == 0){
  return 1;
 }else{
  *b = *b + *a;
  *a = *a-1;
  return summe(a,b);
 }
}