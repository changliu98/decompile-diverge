int area(int *list,int length){
 int i;
 int area = 0;

 for(i=length-1;i>=0;i--){
  area += list[i]*i - list[i]*(length-1-i);
 }

 return area;
}