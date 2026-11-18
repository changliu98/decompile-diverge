int maxIndex(float *array){
 int index = 0;
 float max = array[0];
 for(int i=0;i<3;i++){
  if(array[i] > max){
   index = i;
   max = array[i];
  }
 }
 return index;
}