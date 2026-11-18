int func0(double *list1,int length)

{
  double dVar1;
  int sum;
  int i;
  int length_local;
  double *list1_local;
  
  sum = 0;
  for (i = 0; i < length; i = i + 1) {
    dVar1 = round(list1[i]);
    sum = (int)((double)sum + dVar1);
  }
  return sum * length;
}