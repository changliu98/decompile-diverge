float func0(float *data, int n){
 float max = -99999;
 int i;
 for(i=0;i<n;i++){
  if(data[i]>max) max=data[i];
 }
 return max;
}