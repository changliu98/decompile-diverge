float max(float *tab, int size){
 float max = -10000.0;
 int i = 0;
 for(i=0;i<size;i++){
  if(tab[i]>max){
   max = tab[i];
  }
 }
 return max;
}