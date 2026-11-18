void initialize_temp(unsigned int *a,unsigned int *t){
 int i,j;
 for(i = 9,j=14 ; i>=0 ; i--,j--)
  t[j] = a[i];
 while(j+1)
  t[j--] = 0;
}