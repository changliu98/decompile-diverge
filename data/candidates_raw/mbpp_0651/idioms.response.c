int is_subset(int *test_tup1, int n1, int *test_tup2, int n2){
 int i; int j;
 for(i = 0; i < n2; i++){
  int found = 0;
  for(j = 0; j < n1; j++){
   if(test_tup2[i] == test_tup1[j]){
    found = 1;
    break;
   }
  }
  if(!found){
   return 0;
  }
 }
 return 1;
}