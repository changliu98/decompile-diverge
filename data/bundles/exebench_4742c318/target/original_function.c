float mayorDif(float arrayLineal[]) {
 float mayor, mayorTemp;
 int i;
 mayor = mayorTemp = 0;
 for ( i = 0; arrayLineal[i+1] != 0; i++) {
  mayorTemp = arrayLineal[i] - arrayLineal[i+1];
  mayorTemp = ((mayorTemp) >= 0? mayorTemp: -mayorTemp);
  if(mayorTemp > mayor)
   mayor = mayorTemp;
 }
 return mayor;
}