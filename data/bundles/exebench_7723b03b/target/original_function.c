void sort(char *a){
 int i,j,k;
 for (i=0;a[i+1];i++) {
  k=a[i+1];
  for (j=i;a[j]>k&&j>0;j--) {
   a[j+1]=a[j];
  }
  a[j+1]=k;
 }
}