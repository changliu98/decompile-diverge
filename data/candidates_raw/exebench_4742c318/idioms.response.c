float maxDesviacion(float *arrayLineal){
 float mayor = 0;
 float mayorTemp;
 int i = 0;
 while(arrayLineal[i+1]!=0){
  mayorTemp=arrayLineal[i]-arrayLineal[i+1];
  if(mayorTemp<0){
   mayorTemp=-mayorTemp;
  }
  if(mayorTemp>mayor){
   mayor=mayorTemp;
  }
  i++;
 }
 return mayor;
}