float calcularMayorVariacion(float *lineal){
 float mayor = 0, temp = 0;
 int i = 0;
 while(1){
  if(lineal[i+1] == 0)
   return mayor;
  temp = lineal[i] - lineal[i+1];
  temp = temp >= 0 ? temp : -temp;
  if(temp > mayor)
   mayor = temp;
  i++;
 }
}